/*$Id: ms2preproc.cpp 2725 2009-11-30 22:27:57Z marc.kirchner@childrens.harvard.edu $*/

/*
 * ms2preproc.cpp
 *
 * Copyright (c) 2010 Marc Kirchner <marc.kirchner@childrens.harvard.edu>
 * Copyright (c) 2009 Marc Kirchner <marc.kirchner@childrens.harvard.edu>
 *
 * This file is part of mgfp.
 *
 * ms++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ms++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ms++. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <algorithm>

#include <boost/program_options.hpp>

#include <mgfp/Driver.h>
#include <mgfp/Context.h>
#include <mgfp/MgfFile.h>

// #define DEBUG

struct LessThanMass
{
    bool operator()(const mgf::MassAbundancePair& lhs, const mgf::MassAbundancePair& rhs) {
        return lhs.first < rhs.first;
    }
    bool operator()(const double lhs, const mgf::MassAbundancePair& rhs) {
        return lhs < rhs.first;
    }
    bool operator()(const mgf::MassAbundancePair& lhs, const double rhs) {
        return lhs.first < rhs;
    }
};

struct LessThanAbundance 
{
    bool operator()(const mgf::MassAbundancePair& lhs, const mgf::MassAbundancePair& rhs) {
        return lhs.second < rhs.second;
    }
    bool operator()(const double lhs, const mgf::MassAbundancePair& rhs) {
        return lhs < rhs.second;
    }
    bool operator()(const mgf::MassAbundancePair& lhs, const double rhs) {
        return lhs.second < rhs;
    }
};

namespace Ms2Preproc {


/** Functor to determine the top X peaks in a given set of peaks.
 */
class TopX
{
    public:
        TopX(unsigned int x) : x_(x)
        {}

        template<class In, class Out, class Comp>
        Out operator()(In begin, In end, Out out, Comp comp) {
            typename In::difference_type size = std::distance(begin, end);
#ifdef DEBUG
if (size > 0) {
    std::cerr << "range " << begin->first << " - " << (end-1)->first << std::endl;
}
#endif

            // FIXME: Make the static_cast in the next step safe.
            if (static_cast<unsigned int>(size) > x_) {
                // sort a copy
                std::vector<typename In::value_type> v(begin, end);
                std::sort(v.begin(), v.end(), comp);
                std::copy(v.rbegin(), v.rbegin()+x_, out);
#ifdef DEBUG
if (size > 0) {
    for (typename std::vector<typename In::value_type>::iterator i = v.end()-x_; i != v.end() ; ++i) {
        std::cerr << '\t' << i->first << " " << i->second << std::endl;
    }
}
#endif
                std::advance(out, x_);
            } else {
#ifdef DEBUG
if (size > 0) {
    for (In i = begin; i != end ; ++i) {
        std::cerr << '\t' << i->first << " " << i->second << std::endl;
    }
}
#endif
                // accept all peaks
                std::copy(begin, end, out);
                std::advance(out, size);
            }
            return out;
        }
    protected:
        unsigned int x_;
};

/** Functor to determine the top X peaks in Y regions for a given set of peaks.
 */
class TopXInYRegions
{
    public:
        TopXInYRegions(unsigned int x, unsigned int y) : x_(x), y_(y)
        {}

        template<class In, class Out, class MassComp, class AbundanceComp>
        Out operator()(In begin, In end, Out out, MassComp massComp, AbundanceComp abundanceComp) {
            // sort a copy
            std::vector<typename In::value_type> v(begin, end);
            std::sort(v.begin(), v.end(), massComp);
            // split the m/z domain in y_ equisized regions
            double maxMz = (v.end()-1)->first;
            double minMz = (v.begin())->first;
            double increment = (maxMz - minMz) / static_cast<double>(y_);
            TopX topX(x_);
            if (increment > 2.5) {
                for (unsigned int k = 0; k < y_; ++k) {
#ifdef DEBUG
std::cerr << '#' <<  minMz + k*increment - 2.5 << " - " <<  minMz + (k+1)*increment + 2.5 << std::endl;
#endif
                    // iterate over all regions and apply TopX
                    double regionBegin = minMz + k*increment - 2.5;
                    regionBegin = regionBegin > minMz ? regionBegin : minMz;
                    double regionEnd =  minMz + (k+1)*increment + 2.5;
                    In regionBeginIt = lower_bound(v.begin(), v.end(), regionBegin, massComp);
                    In regionEndIt = upper_bound(v.begin(), v.end(), regionEnd, massComp);
                    // run TopX on region
                    Out nout = topX(regionBeginIt, regionEndIt, out, abundanceComp);
#ifdef DEBUG
std::cerr << "step " << k << " of " << y_ << ": topX returned " << nout-out << " peaks." << std::endl;
#endif
                    out = nout;

                }
            } else {
                Out nout = topX(v.begin(), v.end(), out, abundanceComp);
#ifdef DEBUG
std::cerr << "increment too small: topX returned " << nout-out << " peaks." << std::endl;
#endif
                out = nout;
            }
            return out;
        }
    private:
        unsigned int x_, y_;
};

/** Functor to determine the top X peaks in windows of size Z.
 */
class TopXInWindowsOfSizeZ
{
    public:
        TopXInWindowsOfSizeZ(unsigned int x, double z) : x_(x), z_(z)
        {
#ifdef DEBUG
std::cerr << "got: " << z_ << std::endl;
#endif
        }

        template <class In, class Out, class MassComp, class AbundanceComp>
        Out operator()(In begin, In end, Out out, MassComp massComp, AbundanceComp abundanceComp) {
            // get a copy
            std::vector<typename In::value_type> v(begin, end);
            TopX topX(x_);

            while (!v.empty()) {
                // sort by abundance
                std::sort(v.begin(), v.end(), abundanceComp);
                double maxAbundanceMass = v[v.size()-1].first;
                // sort by mass
                std::sort(v.begin(), v.end(), massComp);
                // define window
#ifdef DEBUG
std::cerr << '#' << maxAbundanceMass - z_ << '-' << maxAbundanceMass + z_ << std::endl;
#endif
                In regionBegin = lower_bound(v.begin(), v.end(), maxAbundanceMass - z_, massComp);
                In regionEnd = upper_bound(regionBegin, v.end(), maxAbundanceMass + z_, massComp);
                // get TopX
                out = topX(regionBegin, regionEnd, out, abundanceComp);
                // erase entries in window
                v.erase(regionBegin, regionEnd);
            }
            return out;
        }

    private:
        unsigned int x_;
        double z_;
};

}

namespace dta {

/** A DTA spectrum. Quick hack for the ms2preproc executable until we have a better concept for annotated spectra.
 */
class DtaSpectrum : public mgf::Collection<mgf::MassAbundancePair> {
    public:
        void setPrecursorMass(const double m) { precursorMass_ = m; }
        double getPrecursorMass() const { return precursorMass_; }
        void setCharge(const int c) { charge_ = c; }
        int getCharge() const { return charge_; }
        void setScans(const std::pair<unsigned int, unsigned int>& scans) { scans_ = scans; }
        std::pair<unsigned int, unsigned int> getScans() const { return scans_; }
        void clear() {
            precursorMass_ = 0.0;
            charge_ = 0;
            scans_ = std::make_pair(0,0);
            mgf::Collection<mgf::MassAbundancePair>::clear();
        }
    private:
        MGFP_EXPORT friend std::ostream& operator<<(std::ostream& os, DtaSpectrum& s);
        double precursorMass_;
        int charge_;
        std::pair<unsigned int, unsigned int> scans_;
};

/** A DTA parser that fills a DTA spectrum. Should also be integrated with ms++. Implementation trivial.
 */
class DtaParser {
    public:
        void parse(const std::string& filename, DtaSpectrum& s) {
            // TODO: add some filename parsing here to obtain the
            // scan numbers (DTA is *such* a horrible format).

            // open file and parse contents
            std::ifstream ifs(filename.c_str());
            if (ifs) {
                s.clear();
                // first line is precursor mass and charge
                double precursorMass;
                int charge;
                ifs >> precursorMass >> charge;
                s.setPrecursorMass(precursorMass);
                s.setCharge(charge);
                // afterwards there are mass/abundance pairs
                double m, ab;
                ifs >> m >> ab;
                while(!ifs.eof()) {
                    s.push_back(std::make_pair(m, ab));
                    ifs >> m >> ab;
                }
            } else {
                throw std::invalid_argument("file not found.");
            }
        }
};

std::ostream& operator<<(std::ostream& os, DtaSpectrum& s) {
    os << s.precursorMass_ << " " << s.charge_ << std::endl;
    for (DtaSpectrum::const_iterator i = s.begin(); i != s.end(); ++i) {
        os << i-> first << " " << i->second << std::endl;
    }
    return os;
}

}

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    try {

        // Declare the supported options.
        // FIXME: add version info.
        po::options_description desc("MS/MS preprocessor executable, Copyright 2009-10 Marc Kirchner.\n"
            "Please cite as:\n"
            " Renard BY, Kirchner M, Monigatti F, Invanov AR, Rappsilber J,\n"
            " Winter D, Steen JAJ, Hamprecht FA, Steen H, When Less Can Yield\n"
            " More - Computational Preprocessing of MS/MS Spectra for\n"
            " Peptide Identification, Proteomics (2009).\n\nValid arguments are"
            );
        unsigned int precision(0);
        std::string format;
        desc.add_options()
            ("help,h", "produce this help message")
            ("infile,i", po::value<std::string>(), "name of the MGF/DTA input file")
            ("outfile,o", po::value<std::string>(), "name of the MGF output file")
            ("format,f", po::value<std::string>(&format)->default_value(std::string("mgf")), "input format: (dta|mgf)")
            ("top,X", po::value<int>(), "number of highest intensity ions to keep")
            ("nregions,Y", po::value<int>(), "number of equal-sized regions the MS/MS spectrum is split into")
            ("winsize,Z", po::value<double>(), "m/z window (+/-Z) around high-intensity peaks in which the top X are selected")
            ("verbose,v", "toggle verbose output")
            ("precision,p", po::value<unsigned int>(&precision)->default_value(4), "precision of output")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            std::cerr << desc << std::endl;
            return 1;
        }

        // input sanity checking
        if (!(vm.count("infile") && vm.count("outfile"))) {
            std::cerr << desc << std::endl << "ERROR: "
            "Need 'infile' and 'outfile' arguments." << std::endl;
            return 1;
        }
        if (!(vm.count("top"))) {
            std::cerr << desc << std::endl << "ERROR: "
            "Need 'top,X' argument." << std::endl;
            return 1;
        }
		if (vm.count("nregions") > 0 && vm.count("winsize") > 0) {
            std::cerr << desc << std::endl << "ERROR: "
            "Parameters 'nregions' and 'winsize' cannot be specified together." << std::endl;
            return 1;
        }
        if (!(format == "mgf" || format == "dta")) {
            std::cerr << desc << std::endl << "ERROR: "
            "Format must be one of 'mgf' or 'dta'." << std::endl;
            return 1;
        }
        // logging/debug output
        bool trace = vm.count("verbose") > 0 ? true : false;
        // I/O
        std::string infilename(vm["infile"].as<std::string>());
        std::string outfilename(vm["outfile"].as<std::string>());
        std::ofstream out(outfilename.c_str());
        if (!out.good()) {
            return -1;
        }
        // check format
        // common variables
        int x = vm["top"].as<int>();
        // check which format we are dealing with: in the case of MGF
        // we need to invoke the parser, read a whole collection of
        // spectra and apply the operators to each spectrum. In the
        // case of DTA, we deal with a single spectrum only.
        //
        // This is some ugly code duplication between the two cases; oh, well...
        //
        if (format == "mgf") {
            // set up context
            mgf::MgfFile s;
            mgf::Driver driver(s);
            driver.trace_parsing = trace;
            driver.trace_scanning = trace;

            // I/O: input
            std::ifstream in(infilename.c_str());
            if (!in.good()) {
                return -1;
            }

            // parse input into memory
            bool result = driver.parse_stream(in);
            if (!result) {
                return -1;
            }

            // set info
            out << "# MGF created using ms2preproc, (c) 2009 Marc Kirchner.\n"
                << "# This program accompanies Renard BY, Kirchner M, Monigatti F, Invanov AR,\n"
                << "# Rappsilber J, Winter D, Steen JAJ, Hamprecht FA, Steen H, When Less\n"
                << "# Can Yield More - Computational Preprocessing of MS/MS Spectra for\n"
                << "# Peptide Identification, Proteomics (2009).\n"
                << "# Command: " << argv[0];
            for (int i = 1; i < argc; ++i) {
                out << " " << argv[i];
            }
            out << "." << std::endl;

            // get a handle to the data
            typedef mgf::MgfFile::iterator Iterator;

            if (vm.count("nregions")) {
                // Top X in Y regions
                int y = vm["nregions"].as<int>();
                Ms2Preproc::TopXInYRegions topXInYRegions(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
                for (Iterator i = s.begin(); i != s.end(); ++i) {
                    // get a temporary object and make sure it is big enough
                    mgf::MgfSpectrum m;
                    m.resize(2*i->size());
                    // get the top X in Y regions, including duplicated from overlaps
                    mgf::MgfSpectrum::iterator sEnd = topXInYRegions(i->begin(), i->end(), m.begin(), LessThanMass(), LessThanAbundance());
                    // make sure we have enough space in the original object
                    i->resize(std::distance(m.begin(), sEnd));
                    // unique copy expectes a sorted range
                    std::sort(m.begin(), sEnd, LessThanMass());
                    // copy all unique peaks back into the original MgfSpectrum
                    mgf::MgfSpectrum::iterator iEnd = std::unique_copy(m.begin(), sEnd, i->begin());
                    // crop to fit
                    i->resize(std::distance(i->begin(), iEnd));
                }
            } else if (vm.count("winsize")) {
                // Top X in windows of size Z
                double z = vm["winsize"].as<int>();
                Ms2Preproc::TopXInWindowsOfSizeZ topXInWindowsOfSizeZ(static_cast<unsigned int>(x), z);
                for (Iterator i = s.begin(); i != s.end(); ++i) {
                    mgf::MgfSpectrum::iterator trash = topXInWindowsOfSizeZ(i->begin(), i->end(), i->begin(), LessThanMass(), LessThanAbundance());
                    i->erase(trash, i->end());
                    std::sort(i->begin(), i->end(), LessThanMass()); // not necessary
                }
            } else {
                // Top X
                Ms2Preproc::TopX topX(static_cast<unsigned int>(x));
                for (Iterator i = s.begin(); i != s.end(); ++i) {
                     mgf::MgfSpectrum::iterator trash = topX(i->begin(), i->end(), i->begin(), LessThanAbundance());
                    i->erase(trash, i->end());
                    std::sort(i->begin(), i->end(), LessThanMass());
                }
            }
            out.setf(std::ios_base::fixed, std::ios_base::floatfield);
            out.precision(precision);
            out << s << std::endl;
        } else if (format == "dta") {
            dta::DtaParser parser;
            dta::DtaSpectrum s;
            // read DTA spectrum
            parser.parse(infilename, s);
            if (vm.count("nregions")) {
                // Top X in Y regions
                int y = vm["nregions"].as<int>();
                Ms2Preproc::TopXInYRegions topXInYRegions(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
                // get a temporary object and make sure it is big enough
                mgf::MgfSpectrum tmp;
                tmp.resize(2*s.size());
                // get the top X in Y regions, including duplicated from overlaps
                mgf::MgfSpectrum::iterator tmpEnd = topXInYRegions(s.begin(), s.end(), tmp.begin(), LessThanMass(), LessThanAbundance());
                // make sure we have enough space in the original object
                s.resize(std::distance(tmp.begin(), tmpEnd));
                // unique copy expectes a sorted range
                std::sort(tmp.begin(), tmpEnd, LessThanMass());
                // copy all unique peaks back into the original MgfSpectrum
                mgf::MgfSpectrum::iterator sEnd = std::unique_copy(tmp.begin(), tmpEnd, s.begin());
                // crop to fit
                s.resize(std::distance(s.begin(), sEnd));
            } else if (vm.count("winsize")) {
                // Top X in windows of size Z
                double z = vm["winsize"].as<int>();
                Ms2Preproc::TopXInWindowsOfSizeZ topXInWindowsOfSizeZ(static_cast<unsigned int>(x), z);
                mgf::MgfSpectrum::iterator trash = topXInWindowsOfSizeZ(s.begin(), s.end(), s.begin(), LessThanMass(), LessThanAbundance());
                s.erase(trash, s.end());
                std::sort(s.begin(), s.end(), LessThanMass()); // not necessary
            } else {
                // Top X
                Ms2Preproc::TopX topX(static_cast<unsigned int>(x));
                mgf::MgfSpectrum::iterator trash = topX(s.begin(), s.end(), s.begin(), LessThanAbundance());
                s.erase(trash, s.end());
                std::sort(s.begin(), s.end(), LessThanMass());
            }
            out.setf(std::ios_base::fixed, std::ios_base::floatfield);
            out.precision(precision);
            out << s << std::endl;
        }
        return 0;
    }   catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return (-1);
}

