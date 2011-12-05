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

#ifndef MGFFILEPRINTER_HPP_
#define MGFFILEPRINTER_HPP_

#include <mgf/Driver.h>
#include <mgf/Context.h>
#include <mgf/MgfFile.h>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>

#include <boost/shared_ptr.hpp>

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


#endif /* MGFFILEPRINTER_HPP_ */
