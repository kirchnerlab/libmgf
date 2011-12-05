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

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfInputFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFInputFile"));

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfOutputFile1 =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFOutputFile1"));
            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfOutputFile2 =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFOutputFile2"));
            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfOutputFile3 =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFOutputFile3"));
            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfOutputFile4 =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFOutputFile4"));


            mgfInputFile->lock();
            mgfOutputFile1->lock();
            mgfOutputFile2->lock();
            mgfOutputFile3->lock();
            mgfOutputFile4->lock();

            if (mgfOutputFile1->get()->size() > 0) {
                LIBPIPE_PIPELINE_TRACE(req, "MGF File already splited");

            } else {
                LIBPIPE_PIPELINE_TRACE(req, "Starting spliting MGF File");

                int div = mgfInputFile->get()->size() / 4;

                mgf::MgfFile* temp1 = new mgf::MgfFile;
                mgf::MgfFile* temp2 = new mgf::MgfFile;
                mgf::MgfFile* temp3 = new mgf::MgfFile;
                mgf::MgfFile* temp4 = new mgf::MgfFile;

                mgf::MgfFile::iterator it = mgfInputFile->get()->begin();

                temp1->assign(it, it + div);
                it = it + div;
                temp2->assign(it, it + div);
                it = it + div;
                temp3->assign(it, it + div);
                it = it + div;
                temp4->assign(it, mgfInputFile->get()->end());

                mgfOutputFile1->set(temp1);
                mgfOutputFile2->set(temp2);
                mgfOutputFile3->set(temp3);
                mgfOutputFile4->set(temp4);
                LIBPIPE_PIPELINE_TRACE(req, "MGF File successful splited.");

            }

            mgfOutputFile1->unlock();
            mgfOutputFile2->unlock();
            mgfOutputFile3->unlock();
            mgfOutputFile4->unlock();
            mgfInputFile->unlock();

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



} /* namespace Ms2Preproc_libpipe */
#endif /* MGFFILEREADER_H_ */
