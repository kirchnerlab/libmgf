/*$Id$*/
/*
 * mgfvalidate.cpp
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

#include <iostream>
#include <boost/program_options.hpp>
#include <mgfp/mgfp.h>

int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    bool verbose = false;
    desc.add_options()
        ("help,h", "produce help message")
        ("verbose,v", po::value(&verbose)->zero_tokens(), "verbose output (good to pinpoint parsing errors)")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
    
    // prepare the parser
    mgf::Context context;
    mgf::Driver driver(context);
    driver.trace_parsing = verbose;
    driver.trace_scanning = verbose;

    // parse input into memory
    bool result = driver.parse_stream(std::cin);
    if (!result) {
        std::cerr << "Error parsing data stream." << std::endl;
        return -1;
    }
    return 0;
}

