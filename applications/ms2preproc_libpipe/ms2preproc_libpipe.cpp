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

