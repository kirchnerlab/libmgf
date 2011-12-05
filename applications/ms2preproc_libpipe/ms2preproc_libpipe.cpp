/*
 * ms2preproc_libpipe.cpp
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

#include <fstream>

#include <boost/program_options.hpp>

#include <libpipe/rtc/PipelineLoader.hpp>
#include <boost/algorithm/string.hpp>

#include "Algorithms/util.hpp"
#include "Algorithms/MgfFileReader.hpp"
#include "Algorithms/MGFFilePrinter.hpp"
#include "Algorithms/TopXAlgorithm.hpp"
#include "Algorithms/TopXInWindowsOfSizeZAlgorithm.hpp"
#include "Algorithms/TopXInYRegionsAlgorithm.hpp"
#include "Algorithms/MGFFilePrinterMerge.hpp"
#include "Algorithms/MgfFileSpliter.hpp"


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
            po::value<std::string>(),
            "name of the input file which contains the path to the"
                " libpipe input files");

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

