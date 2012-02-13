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

#ifndef MGF_FILE_SPLITER_FOUR_HPP_
#define MGF_FILE_SPLITER_FOUR_HPP_

#include <mgf/MgfFile.h>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>

#include <boost/shared_ptr.hpp>

namespace Ms2Preproc {


class MgfFileSpliterFour : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new MgfFileSpliterFour;
        }

        virtual ~MgfFileSpliterFour()
        {
        }

        void update(libpipe::Request& req)
        {


            LIBPIPE_PREPARE_WRITE_ACCESS(mgfOutputFile1, mgfOutputFile1Data,
                mgf::MgfFile, "MGFOutputFile1");
            LIBPIPE_PREPARE_WRITE_ACCESS(mgfOutputFile2, mgfOutputFile2Data,
                mgf::MgfFile, "MGFOutputFile2");
            LIBPIPE_PREPARE_WRITE_ACCESS(mgfOutputFile3, mgfOutputFile3Data,
                mgf::MgfFile, "MGFOutputFile3");
            LIBPIPE_PREPARE_WRITE_ACCESS(mgfOutputFile4, mgfOutputFile4Data,
                mgf::MgfFile, "MGFOutputFile4");
            LIBPIPE_PREPARE_WRITE_ACCESS(mgfInputFile, mgfInputFileData,
                            mgf::MgfFile, "MGFInputFile");



            if (mgfOutputFile1Data.size() > 0) {
                LIBPIPE_PIPELINE_TRACE("MGF File already splited");

            } else {
                LIBPIPE_PIPELINE_TRACE("Starting spliting MGF File");

                int div = mgfInputFileData.size() / 4;

                mgf::MgfFile* temp1 = new mgf::MgfFile;
                mgf::MgfFile* temp2 = new mgf::MgfFile;
                mgf::MgfFile* temp3 = new mgf::MgfFile;
                mgf::MgfFile* temp4 = new mgf::MgfFile;

                mgf::MgfFile::iterator it = mgfInputFileData.begin();

                temp1->assign(it, it + div);
                it = it + div;
                temp2->assign(it, it + div);
                it = it + div;
                temp3->assign(it, it + div);
                it = it + div;
                temp4->assign(it, mgfInputFileData.end());

                mgfOutputFile1->set(temp1);
                mgfOutputFile2->set(temp2);
                mgfOutputFile3->set(temp3);
                mgfOutputFile4->set(temp4);
                LIBPIPE_PIPELINE_TRACE("MGF File successful splited.");

            }

            LIBPIPE_CLEAR_ACCESS(mgfOutputFile1);
            LIBPIPE_CLEAR_ACCESS(mgfOutputFile2);
            LIBPIPE_CLEAR_ACCESS(mgfOutputFile3);
            LIBPIPE_CLEAR_ACCESS(mgfOutputFile4);
            LIBPIPE_CLEAR_ACCESS(mgfInputFile);

        }

    protected:

    private:
        MgfFileSpliterFour() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFInputFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFOutputFile1"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
            ports_["MGFOutputFile2"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
            ports_["MGFOutputFile3"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
            ports_["MGFOutputFile4"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
        }

        static const bool registerLoader()
        {
            std::string ids = "MgfFileSpliterFour";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                MgfFileSpliterFour::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool MgfFileSpliterFour::registered_ = registerLoader();


} /* namespace Ms2Preproc */
#endif /* MGF_FILE_SPLITER_FOUR_HPP_ */
