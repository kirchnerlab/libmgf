/*
 * ms2preproc.cpp
 *
 * Copyright (c) 2009-2011 Marc Kirchner
 *                    2011 David Sichau
 *
 * This file is part of libmgf.
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
#include <map>

#include <boost/program_options.hpp>

#include <mgf/Driver.h>
#include <mgf/Context.h>
#include <mgf/MgfFile.h>
#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/rtc/PipelineLoader.hpp>
#include <libpipe/utilities/Parameters.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

// #define DEBUG

struct LessThanMass
{
        bool operator()(const mgf::MassAbundancePair& lhs,
            const mgf::MassAbundancePair& rhs)
        {
            return lhs.first < rhs.first;
        }
        bool operator()(const double lhs, const mgf::MassAbundancePair& rhs)
        {
            return lhs < rhs.first;
        }
        bool operator()(const mgf::MassAbundancePair& lhs, const double rhs)
        {
            return lhs.first < rhs;
        }
};

struct LessThanAbundance
{
        bool operator()(const mgf::MassAbundancePair& lhs,
            const mgf::MassAbundancePair& rhs)
        {
            return lhs.second < rhs.second;
        }
        bool operator()(const double lhs, const mgf::MassAbundancePair& rhs)
        {
            return lhs < rhs.second;
        }
        bool operator()(const mgf::MassAbundancePair& lhs, const double rhs)
        {
            return lhs.second < rhs;
        }
};

namespace Ms2Preproc {

class MgfFileReader : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new MgfFileReader;
        }

        virtual ~MgfFileReader()
        {
        }

        void update(libpipe::Request& req)
        {
            std::string infilename = parameters_.get<std::string>(
                "infilename");
            bool trace = parameters_.get<bool>("verbose");

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfInputFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFInputFile"));
            LIBPIPE_PIPELINE_TRACE(req, "Starting Reading MGF File");

            mgfInputFile->lock();

            mgf::MgfFile s;
            mgf::Driver driver(*mgfInputFile->get());
            driver.trace_parsing = trace;
            driver.trace_scanning = trace;

            // I/O: input
            std::ifstream in(infilename.c_str());
            if (!in.good()) {
                libpipe_fail("error in reading input file");
            }

            // parse input into memory
            bool result = driver.parse_stream(in);
            if (!result) {
                libpipe_fail("error in parsing input file to memory");
            }
            mgfInputFile->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "MGF File successful read.");
        }

    protected:

    private:
        MgfFileReader() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFInputFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
        }

        static const bool registerLoader()
        {
            std::string ids = "MgfFileReader";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                MgfFileReader::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool MgfFileReader::registered_ = registerLoader();

class MgfFilePrinter : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new MgfFilePrinter;
        }

        virtual ~MgfFilePrinter()
        {
        }

        void update(libpipe::Request& req)
        {

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfOutputFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFParseFile"));
            LIBPIPE_PIPELINE_TRACE(req, "Starting writting MGF File");

            std::string outfilename = parameters_.get<std::string>("outfile");
            std::ofstream out(outfilename.c_str());
            if (!out.good()) {
                libpipe_fail("Error in generating output file");
            }
            out
                    << "# MGF created using ms2preproc, (c) 2009 Marc Kirchner.\n"
                    << "# This program accompanies Renard BY, Kirchner M, Monigatti F, Invanov AR,\n"
                    << "# Rappsilber J, Winter D, Steen JAJ, Hamprecht FA, Steen H, When Less\n"
                    << "# Can Yield More - Computational Preprocessing of MS/MS Spectra for\n"
                    << "# Peptide Identification, Proteomics (2009).\n";

            out << std::endl;

            out.setf(std::ios_base::fixed, std::ios_base::floatfield);
            out.precision(parameters_.get<unsigned int>("precision"));

            mgfOutputFile->lock();
            out << *mgfOutputFile->get() << std::endl;
            mgfOutputFile->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "MGF File successful written.");
        }

    protected:

    private:
        MgfFilePrinter() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFParseFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
        }

        static const bool registerLoader()
        {
            std::string ids = "MgfFilePrinter";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                MgfFilePrinter::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool MgfFilePrinter::registered_ = registerLoader();

class TopXAlgorithm : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new TopXAlgorithm;
        }

        virtual ~TopXAlgorithm()
        {
        }

        void update(libpipe::Request& req)
        {

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfInputFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFInputFile"));
            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfParsedFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFParsedFile"));
            LIBPIPE_PIPELINE_TRACE(req, "Starting TopX");

            mgfInputFile->shared_lock();
            mgfParsedFile->lock();
            // copy the file so that input is not changed.
            mgfParsedFile->set(new mgf::MgfFile(*mgfInputFile->get()));
            mgfInputFile->unlock();

            for (mgf::MgfFile::iterator i = mgfParsedFile->get()->begin();
                    i != mgfParsedFile->get()->end(); ++i) {
                mgf::MgfSpectrum::iterator trash = run(i->begin(), i->end(),
                    i->begin(), LessThanAbundance());
                i->erase(trash, i->end());
                std::sort(i->begin(), i->end(), LessThanMass());
            }

            mgfParsedFile->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "TopX is finished");

        }

    protected:

    private:
        TopXAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFInputFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFParsedFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
        }

        template<class In, class Out, class Comp>
        Out run(In begin, In end, Out out, Comp comp)
        {
            typename In::difference_type size = std::distance(begin, end);
            unsigned int x = parameters_.get<unsigned int>("top");

            // FIXME: Make the static_cast in the next step safe.
            if (static_cast<unsigned int>(size) > x) {
                // sort a copy
                std::vector<typename In::value_type> v(begin, end);
                std::sort(v.begin(), v.end(), comp);
                std::copy(v.rbegin(), v.rbegin() + x, out);
                std::advance(out, x);
            } else {
                // accept all peaks
                std::copy(begin, end, out);
                std::advance(out, size);
            }
            return out;
        }

        static const bool registerLoader()
        {
            std::string ids = "TopXAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                TopXAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool TopXAlgorithm::registered_ = registerLoader();

class TopXInYRegionsAlgorithm : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new TopXInYRegionsAlgorithm;
        }

        virtual ~TopXInYRegionsAlgorithm()
        {
        }

        void update(libpipe::Request& req)
        {

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfInputFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFInputFile"));
            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfParsedFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFParsedFile"));
            LIBPIPE_PIPELINE_TRACE(req, "Starting TopXInYRegions");

            mgfInputFile->shared_lock();
            mgfParsedFile->lock();
            // copy the file so that input is not changed.
            mgfParsedFile->set(new mgf::MgfFile(*mgfInputFile->get()));
            mgfInputFile->unlock();

            // Top X in Y regions

            for (mgf::MgfFile::iterator i = mgfParsedFile->get()->begin();
                    i != mgfParsedFile->get()->end(); ++i) {
                // get a temporary object and make sure it is big enough
                mgf::MgfSpectrum m;
                m.resize(2 * i->size());
                // get the top X in Y regions, including duplicated from overlaps
                mgf::MgfSpectrum::iterator sEnd = run(i->begin(), i->end(),
                    m.begin(), LessThanMass(), LessThanAbundance());
                // make sure we have enough space in the original object
                i->resize(std::distance(m.begin(), sEnd));
                // unique copy expectes a sorted range
                std::sort(m.begin(), sEnd, LessThanMass());
                // copy all unique peaks back into the original MgfSpectrum
                mgf::MgfSpectrum::iterator iEnd = std::unique_copy(m.begin(),
                    sEnd, i->begin());
                // crop to fit
                i->resize(std::distance(i->begin(), iEnd));
            }

            mgfParsedFile->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "TopXInYRegions is finished");

        }

    protected:

    private:
        TopXInYRegionsAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFInputFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFParsedFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
        }

        template<class In, class Out, class MassComp, class AbundanceComp>
        Out run(In begin, In end, Out out, MassComp massComp,
            AbundanceComp abundanceComp)
        {
            // sort a copy
            std::vector<typename In::value_type> v(begin, end);
            std::sort(v.begin(), v.end(), massComp);
            // split the m/z domain in y_ equisized regions
            double maxMz = (v.end() - 1)->first;
            double minMz = (v.begin())->first;
            double increment = (maxMz - minMz)
                    / static_cast<double>(parameters_.get<unsigned int>(
                        "nregions"));
            if (increment > 2.5) {
                for (unsigned int k = 0;
                        k < parameters_.get<unsigned int>("nregions"); ++k) {
                    // iterate over all regions and apply TopX
                    double regionBegin = minMz + k * increment - 2.5;
                    regionBegin = regionBegin > minMz ? regionBegin : minMz;
                    double regionEnd = minMz + (k + 1) * increment + 2.5;
                    In regionBeginIt = std::lower_bound(v.begin(), v.end(),
                        regionBegin, massComp);
                    In regionEndIt = std::upper_bound(v.begin(), v.end(),
                        regionEnd, massComp);
                    // run TopX on region
                    Out nout = runTopX(regionBeginIt, regionEndIt, out,
                        abundanceComp);
                    out = nout;

                }
            } else {
                Out nout = runTopX(v.begin(), v.end(), out, abundanceComp);
                out = nout;
            }
            return out;
        }

        template<class In, class Out, class Comp>
        Out runTopX(In begin, In end, Out out, Comp comp)
        {
            typename In::difference_type size = std::distance(begin, end);
            unsigned int x = parameters_.get<unsigned int>("top");

            // FIXME: Make the static_cast in the next step safe.
            if (static_cast<unsigned int>(size) > x) {
                // sort a copy
                std::vector<typename In::value_type> v(begin, end);
                std::sort(v.begin(), v.end(), comp);
                std::copy(v.rbegin(), v.rbegin() + x, out);
                std::advance(out, x);
            } else {
                // accept all peaks
                std::copy(begin, end, out);
                std::advance(out, size);
            }
            return out;
        }

        static const bool registerLoader()
        {
            std::string ids = "TopXInYRegionsAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                TopXInYRegionsAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool TopXInYRegionsAlgorithm::registered_ = registerLoader();

class TopXInWindowsOfSizeZAlgorithm : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new TopXInWindowsOfSizeZAlgorithm;
        }

        virtual ~TopXInWindowsOfSizeZAlgorithm()
        {
        }

        void update(libpipe::Request& req)
        {

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfInputFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFInputFile"));
            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfParsedFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFParsedFile"));
            LIBPIPE_PIPELINE_TRACE(req, "Starting TopXInWindowsOfSizeZ");

            mgfInputFile->shared_lock();
            mgfParsedFile->lock();
            // copy the file so that input is not changed.
            mgfParsedFile->set(new mgf::MgfFile(*mgfInputFile->get()));
            mgfInputFile->unlock();

            // Top X in windows of size Z
            for (mgf::MgfFile::iterator i = mgfParsedFile->get()->begin();
                    i != mgfParsedFile->get()->end(); ++i) {
                mgf::MgfSpectrum::iterator trash = run(i->begin(), i->end(),
                    i->begin(), LessThanMass(), LessThanAbundance());
                i->erase(trash, i->end());
                std::sort(i->begin(), i->end(), LessThanMass()); // not necessary
            }

            mgfParsedFile->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "TopXInWindowsOfSizeZ is finished");

        }

    protected:

    private:
        TopXInWindowsOfSizeZAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFInputFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFParsedFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
        }

        template<class In, class Out, class MassComp, class AbundanceComp>
        Out run(In begin, In end, Out out, MassComp massComp,
            AbundanceComp abundanceComp)
        {
            // get a copy
            std::vector<typename In::value_type> v(begin, end);

            double z = parameters_.get<double>("winsize");
            while (!v.empty()) {
                // sort by abundance
                std::sort(v.begin(), v.end(), abundanceComp);
                double maxAbundanceMass = v[v.size() - 1].first;
                // sort by mass
                std::sort(v.begin(), v.end(), massComp);
                // define window
                In regionBegin = std::lower_bound(v.begin(), v.end(),
                    maxAbundanceMass - z, massComp);
                In regionEnd = std::upper_bound(regionBegin, v.end(),
                    maxAbundanceMass + z, massComp);
                // get TopX
                out = runTopX(regionBegin, regionEnd, out, abundanceComp);
                // erase entries in window
                v.erase(regionBegin, regionEnd);
            }
            return out;
        }

        template<class In, class Out, class Comp>
        Out runTopX(In begin, In end, Out out, Comp comp)
        {
            typename In::difference_type size = std::distance(begin, end);
            unsigned int x = parameters_.get<unsigned int>("top");

            // FIXME: Make the static_cast in the next step safe.
            if (static_cast<unsigned int>(size) > x) {
                // sort a copy
                std::vector<typename In::value_type> v(begin, end);
                std::sort(v.begin(), v.end(), comp);
                std::copy(v.rbegin(), v.rbegin() + x, out);
                std::advance(out, x);
            } else {
                // accept all peaks
                std::copy(begin, end, out);
                std::advance(out, size);
            }
            return out;
        }

        static const bool registerLoader()
        {
            std::string ids = "TopXInWindowsOfSizeZAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                TopXInWindowsOfSizeZAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool TopXInWindowsOfSizeZAlgorithm::registered_ = registerLoader();
}

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    try {

        // Declare the supported options.
        // FIXME: add version info.
        po::options_description desc(
            "MS/MS preprocessor executable, Copyright 2009-10 Marc Kirchner.\n"
                "Please cite as:\n"
                " Renard BY, Kirchner M, Monigatti F, Invanov AR, Rappsilber J,\n"
                " Winter D, Steen JAJ, Hamprecht FA, Steen H, When Less Can Yield\n"
                " More - Computational Preprocessing of MS/MS Spectra for\n"
                " Peptide Identification, Proteomics (2009).\n\nValid arguments are");

        desc.add_options()("help,h", "produce this help message")("infile,i",
            po::value<std::string>(), "name of the MGF/DTA input file");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cerr << desc << std::endl;
            return 1;
        }

        // input sanity checking
        if (!(vm.count("infile"))) {
            std::cerr << desc << std::endl << "ERROR: "
                    "Need 'infile'  arguments." << std::endl;
            return 1;
        }

        std::string infilename(vm["infile"].as<std::string>());

        std::ifstream inFile(infilename.c_str());
        if (!inFile.good()) {
            return -1;
        }

        std::map<std::string, std::string> inputFiles;
//Parses input file with the libpipe input files
        std::string strOneLine;
        std::string file, key;
        size_t pos;
        getline(inFile, strOneLine);
        while (!strOneLine.empty()) {
            if (strOneLine[0] == '#') {
                getline(inFile, strOneLine);
                continue;
            } else {
                pos = strOneLine.find(":"); // position of ":"
                file = strOneLine.substr(pos + 1);
                boost::trim(file);
                key = strOneLine.substr(0, pos);
                boost::trim(key);
                inputFiles[key] = file;
                getline(inFile, strOneLine);
            }

        }

        inFile.close();

        libpipe::rtc::Pipeline pipeline;
        try {
            libpipe::rtc::PipelineLoader loader(inputFiles);
            pipeline = loader.getPipeline();
        } catch (libpipe::utilities::Exception& e) {
            std::cerr << e.what() << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            pipeline.run();
        } catch (libpipe::utilities::Exception& e) {
            std::cerr << e.what() << std::endl;
        }

        std::vector<std::string> trace;
        trace = pipeline.getTrace();
        for (std::vector<std::string>::const_iterator i = trace.begin();
                i != trace.end(); ++i) {
            std::cout << *i << '\n';
        }
//END PIPELINE
        // set up context

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return (-1);
}

