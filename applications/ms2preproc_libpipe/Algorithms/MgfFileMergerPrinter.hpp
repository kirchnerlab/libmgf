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
#ifndef MGFFILEMERGERPRINTER_HPP_
#define MGFFILEMERGERPRINTER_HPP_

#include <mgf/MgfFile.h>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>

#include <boost/shared_ptr.hpp>

namespace Ms2Preproc {


class MgfFileMergerPrinter : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new MgfFileMergerPrinter;
        }

        virtual ~MgfFileMergerPrinter()
        {
        }

        void update(libpipe::Request& req)
        {

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

            mgfOutputFile1->lock();
            mgfOutputFile2->lock();
            mgfOutputFile3->lock();
            mgfOutputFile4->lock();

            out << *mgfOutputFile1->get() << std::endl;
            out << *mgfOutputFile2->get() << std::endl;
            out << *mgfOutputFile3->get() << std::endl;
            out << *mgfOutputFile4->get() << std::endl;

            mgfOutputFile1->unlock();
            mgfOutputFile2->unlock();
            mgfOutputFile3->unlock();
            mgfOutputFile4->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "MGF File successful written.");
        }

    protected:

    private:
        MgfFileMergerPrinter() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFOutputFile1"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFOutputFile2"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFOutputFile3"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFOutputFile4"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
        }

        static const bool registerLoader()
        {
            std::string ids = "MgfFileMergerPrinter";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                MgfFileMergerPrinter::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool MgfFileMergerPrinter::registered_ = registerLoader();

}



#endif /* MGFFILEMERGERPRINTER_HPP_ */
