/*
 *
 * Copyright (c) 2011 David-Matthias Sichau
 * Copyright (c) 2010 Marc Kirchner
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

#ifndef MGFFILEREADER_H_
#define MGFFILEREADER_H_

#include <fstream>

#include <mgf/Driver.h>
#include <mgf/Context.h>
#include <mgf/MgfFile.h>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>

#include <boost/shared_ptr.hpp>

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


            LIBPIPE_PREPARE_WRITE_ACCESS(mgfInputFile, mgfInputFileData,
                mgf::MgfFile, "MGFInputFile");

            if (mgfInputFile->get()->size() > 0) {
                LIBPIPE_PIPELINE_TRACE("MGF File already stored in memory");
            } else {
                LIBPIPE_PIPELINE_TRACE("Starting Reading MGF File");

                mgf::MgfFile s;
                mgf::Driver driver(mgfInputFileData);
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

                LIBPIPE_PIPELINE_TRACE("MGF File successful read.");
            }
            LIBPIPE_CLEAN_ACCESS(mgfInputFile);

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

} /* namespace Ms2Preproc */
#endif /* MGFFILEREADER_H_ */
