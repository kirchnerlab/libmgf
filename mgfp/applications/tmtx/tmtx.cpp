/*$Id$*/
/*
 * tmtx.cpp
 *
 * Copyright (c) 2010 Marc Kirchner <marc.kirchner@childrens.harvard.edu>
 *
 * This file is part of mgfp.
 * 
 * mgfp is free software: you can redistribute it and/or modify
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

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <tr1/array>
#include <boost/program_options.hpp>
#include <mgfp/mgfp.h>

mgf::MgfSpectrum::iterator findClosestMz(mgf::MgfSpectrum::iterator begin, 
  mgf::MgfSpectrum::iterator end, double referenceMz)
{
    // at least one entry?
    if (begin == end)
        return end;
    // find first entry that is equal or greater than the reference mz
    typedef mgf::MgfSpectrum::iterator MSI;
    MSI pos1 = std::lower_bound(begin, end, referenceMz, mgf::LessThanMz());
    double dist1 = 0.0;
    if (pos1 != end) {
        // found equal or greater
        dist1 = pos1->first - referenceMz;
        if (pos1 == begin || dist1 == 0.0) {
            return pos1;
        }
    } else {
        // return the last entry in the sequence
        pos1 = begin;
        std::advance(pos1, std::distance(begin, end) - 1);
        return pos1;
    }
    // check if the distance to the previous iterator position
    if (pos1 != begin) {
        MSI pos2 = begin;
        std::advance(pos2, std::distance(begin, pos1) - 1);
        double dist2 = referenceMz - pos2->first;
        if (dist2 < dist1) {
            return pos2;
        }
        return pos1;
    }
}
   
enum LabelType { TMT, ITRAQ4, SIZE };
static const size_t sizes[SIZE] = { 10, 8 };
static const double masses[SIZE][10] = 
  {
    { 124.0, 125.0, 126.0, 127.0, 128.0,
      129.0, 130.0, 131.0, 132.0, 133.0 },
    { 112.1, 113.1,  114.1112, 115.1083, 116.1116,
      117.115, 118.1, 119.1, 0.0, 0.0 }};

int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    bool verbose = false;
    std::string inputfile;
    size_t precision;
    desc.add_options()
        ("help,h", "produce help message")
        ("verbose,v", po::value(&verbose)->zero_tokens(), 
         "verbose output (good to pinpoint parsing errors)")
        ("type,t", po::value<std::string>(), "label type: one of TMT, ITRAQ4")
        ("input,i", po::value<std::string>(&inputfile)->default_value("-"),
         "input filename, defaults to stdin")
        ("tee,e", po::value<std::string>(), "run in tee mode: extract label "
          "abundances to specified file and simply pipe MGF data from stdin "
          "to stdout.")
        ("precision,p", po::value<size_t>(&precision)->default_value(6),
         "number of significant digits in output")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
    // check if the user asked for help
    if (vm.count("help") || !vm.count("type")) {
        std::cerr << desc;
        return 1;
    }
    // figure put which labeling technique we use
    LabelType labelType;
    if (vm["type"].as<std::string>() == "TMT") {
        labelType = TMT;
    } else if (vm["type"].as<std::string>() == "ITRAQ4") {
        labelType = ITRAQ4;
    } else {
        std::cerr << vm["type"].as<std::string>() << std::endl;
        std::cerr << desc;
        return 1;
    }
    // initialize the masses
    std::vector<double> labelMasses(sizes[labelType]);
    for (size_t n = 0; n < sizes[labelType]; ++n) {
        labelMasses[n] = masses[labelType][n];
    }
    // prepare the parser
    mgf::MgfFile m;
    mgf::Driver driver(m);
    driver.trace_parsing = verbose;
    driver.trace_scanning = verbose;
    // parse input
    bool result;
    if (inputfile == "-") {
        result = driver.parse_stream(std::cin);
    } else {
        std::ifstream ifs(inputfile.c_str());
        result = driver.parse_stream(ifs);
        ifs.close();
    } 
    if (!result) {
        std::cerr << std::endl 
          << "Error parsing data stream (use -v for details)." << std::endl;
        return -1;
    }
    typedef mgf::MgfFile::iterator MFI;
    // iterate over all spectra
    std::vector<double> obsAbundances(sizes[labelType]);
    for (MFI i = m.begin(); i != m.end(); ++i) {
        // sort
        std::sort(i->begin(), i->end(), mgf::LessThanMz()); 
        typedef mgf::MgfSpectrum::iterator MSI;
        // extract TMT reproter ion intensities
        bool atLeastOneEntry = false;
        for (size_t n = 0; n < sizes[labelType]; ++n) {
            MSI closestIt = findClosestMz(i->begin(), i->end(), labelMasses[n]);
            if (closestIt != i->end()) {
                // check if there is an MS2 centroid 
                if (std::abs(closestIt->first - labelMasses[n]) < 0.4) {
                    obsAbundances[n] = closestIt->second;
                    if (!atLeastOneEntry) atLeastOneEntry = true;
                } else {
                    obsAbundances[n] = 0.0;
                }
            }
        }
        // extract into file
        if (atLeastOneEntry) {
            std::cout << i->getTITLE();
            for (size_t n = 0; n < sizes[labelType]; ++n) {
                std::cout << '\t' << std::setprecision(precision) << obsAbundances[n];
            }
            std::cout << '\n'; // don't use std::endl, save the std::flush.
        }
    }
    return 0;
}

