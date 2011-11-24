/*
 * mgfvalidate.cpp
 *
 * This file is part of mgfp.
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
 *
 */

#include <iostream>
#include <boost/program_options.hpp>
#include <mgf/mgf.h>

int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    bool verbose = false;
    desc.add_options()
        ("help,h", "produce help message")
        ("verbose,v", po::value(&verbose)->zero_tokens(), 
         "verbose output (good to pinpoint parsing errors)")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
    
    // prepare the parser
    mgf::MgfFile mgfFile;
    mgf::Driver driver(mgfFile);
    driver.trace_parsing = verbose;
    driver.trace_scanning = verbose;

    // parse input into memory
    bool result = driver.parse_stream(std::cin);
    if (!result) {
        std::cerr << std::endl 
          << "Error parsing data stream (use -v for details)." << std::endl;
        return -1;
    }
    // print out the titles as we go.
    for (mgf::MgfFile::iterator i = mgfFile.begin(); i != mgfFile.end(); ++i) {
        std::cerr << '"' << i->getTITLE() << '"' << std::endl;
    }
    std::cerr << "Ok." << std::endl;
    return 0;
}

