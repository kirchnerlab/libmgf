/*
 * tmtx.cpp
 *
 * This file is part of libmgf.
 * 
 * Copyright (c) 2010 Marc Kirchner 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <cmath>
#include <iostream>
#include <iterator>
#include <tr1/array>
#include <boost/program_options.hpp>
#include <mgf/mgf.h>

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
   
static const double adductMasses[6] = 
  { 155.0, 156.0, 157.0, 158.0, 159.0, 160.0 };
static const double tmtMasses[6] = 
  { 126.0, 127.0, 128.0, 129.0, 130.0, 131.0 };

int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    bool replace = false;
    bool verbose = false;
    desc.add_options()
        ("help,h", "produce help message")
        ("verbose,v", po::value(&verbose)->zero_tokens(), 
         "verbose output (good to pinpoint parsing errors)")
        ("replace,r", po::value(&replace)->zero_tokens(), 
         "replace TMT intensities in original MGF, output new MGF to stdout.")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
    // check if the user asked for help
    if (vm.count("help")) {
        std::cerr << desc;
        return 1;
    }
    // prepare the parser
    mgf::MgfFile m;
    mgf::Driver driver(m);
    driver.trace_parsing = verbose;
    driver.trace_scanning = verbose;
    // parse input 
    bool result = driver.parse_stream(std::cin);
    if (!result) {
        std::cerr << std::endl 
          << "Error parsing data stream (use -v for details)." << std::endl;
        return -1;
    }
    typedef mgf::MgfFile::iterator MFI;
    // iterate over all spectra
    for (MFI i = m.begin(); i != m.end(); ++i) {
        // sort
        std::sort(i->begin(), i->end(), mgf::LessThanMz()); 
        // extract adduct intensities
        double obsAdductAbundances[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        typedef mgf::MgfSpectrum::iterator MSI;
        for (size_t n = 0; n < 6; ++n) {
            MSI closestIt = findClosestMz(i->begin(), i->end(), adductMasses[n]);
            // check if there is a MS2 centroid 
            if (std::abs(closestIt->first - adductMasses[n]) < 0.5) {
                obsAdductAbundances[n] = closestIt->second;
                if (replace) {
                    // if the replace option is on, remove the observed value
                    // from the spectrum
                    i->erase(closestIt);
                }
            } else {
                obsAdductAbundances[n] = 0.0;
            }
        }
        // extract TMT reproter ion intensities
        double obsTmtAbundances[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        for (size_t n = 0; n < 6; ++n) {
            MSI closestIt = findClosestMz(i->begin(), i->end(), tmtMasses[n]);
            // check if there is a MS2 centroid 
            if (std::abs(closestIt->first - tmtMasses[n]) < 0.5) {
                obsTmtAbundances[n] = closestIt->second;
                if (replace) {
                    // if the replace option is on, remove the observed value
                    // from the spectrum
                    i->erase(closestIt);
                }
            } else {
                obsTmtAbundances[n] = 0.0;
            }
        }
        // add on TMTs
        if (replace) {
            // re-insert 
            for (size_t n = 0; n < 6; ++n) {
                i->push_back(std::make_pair(tmtMasses[n], obsTmtAbundances[n] +
                  obsAdductAbundances[n]));
            }
        } else {
            // extract into file
            std::cout << i->getTITLE();
            for (size_t n = 0; n < 6; ++n) {
                std::cout << '\t' << obsTmtAbundances[n];
            }
            for (size_t n = 0; n < 6; ++n) {
                std::cout << '\t' << obsAdductAbundances[n];
            }
            std::cout << std::endl;
        }
    }
    // if replacement is in effect, output the whole modified file at once.
    if (replace) {
        std::cout << m;
    }
    return 0;
}

