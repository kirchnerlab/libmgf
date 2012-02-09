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

#ifndef TOPXINWINDOWSOFSIZEZALGORITHM_HPP_
#define TOPXINWINDOWSOFSIZEZALGORITHM_HPP_

#include <mgf/Driver.h>
#include <mgf/Context.h>
#include <mgf/MgfFile.h>

#include <libpipe/rtc/Algorithm.hpp>
#include <libpipe/rtc/Pipeline.hpp>
#include <libpipe/rtc/SharedData.hpp>
#include <libpipe/rtc/AlgorithmFactory.hpp>
#include <algorithm>
#include <iterator>

#include <boost/shared_ptr.hpp>

#include "util.hpp"

namespace Ms2Preproc {

class TopXInWindowsOfSizeZAlgorithm : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new TopXInWindowsOfSizeZAlgorithm;
        }

        virtual ~TopXInWindowsOfSizeZAlgorithm()
        {
        }

        void update(libpipe::Request& req)
        {

            LIBPIPE_PREPARE_WRITE_ACCESS(mgfParsedFile, mgfParsedFileData,
                mgf::MgfFile, "MGFParsedFile");

            LIBPIPE_PREPARE_READ_ACCESS(mgfInputFile, mgfInputFileData,
                mgf::MgfFile, "MGFInputFile");

            LIBPIPE_PIPELINE_TRACE("Starting TopXInWindowsOfSizeZ");

            // copy the file so that input is not changed.
            mgfParsedFile->set(new mgf::MgfFile(mgfInputFileData));

            // Top X in windows of size Z
            for (mgf::MgfFile::iterator i = mgfParsedFileData.begin();
                    i != mgfParsedFileData.end(); ++i) {
                mgf::MgfSpectrum::iterator trash = run(i->begin(), i->end(),
                    i->begin(), LessThanMass(), LessThanAbundance());
                i->erase(trash, i->end());
                std::sort(i->begin(), i->end(), LessThanMass()); // not necessary
            }

            LIBPIPE_PIPELINE_TRACE("TopXInWindowsOfSizeZ is finished");
            LIBPIPE_CLEAN_ACCESS(mgfParsedFile);
            LIBPIPE_CLEAN_ACCESS(mgfInputFile);
        }

    protected:

    private:
        TopXInWindowsOfSizeZAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFInputFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFParsedFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
        }

        template<class In, class Out, class MassComp, class AbundanceComp>
        Out run(In begin, In end, Out out, MassComp massComp,
            AbundanceComp abundanceComp)
        {
            // get a copy
            std::vector<typename In::value_type> v(begin, end);

            double z = parameters_.get<double>("winsize");
            while (!v.empty()) {
                // sort by abundance
                std::sort(v.begin(), v.end(), abundanceComp);
                double maxAbundanceMass = v[v.size() - 1].first;
                // sort by mass
                std::sort(v.begin(), v.end(), massComp);
                // define window
                In regionBegin = std::lower_bound(v.begin(), v.end(),
                    maxAbundanceMass - z, massComp);
                In regionEnd = std::upper_bound(regionBegin, v.end(),
                    maxAbundanceMass + z, massComp);
                // get TopX
                out = runTopX(regionBegin, regionEnd, out, abundanceComp);
                // erase entries in window
                v.erase(regionBegin, regionEnd);
            }
            return out;
        }

        template<class In, class Out, class Comp>
        Out runTopX(In begin, In end, Out out, Comp comp)
        {
            typename In::difference_type size = std::distance(begin, end);
            unsigned int x = parameters_.get<unsigned int>("top");

            // FIXME: Make the static_cast in the next step safe.
            if (static_cast<unsigned int>(size) > x) {
                // sort a copy
                std::vector<typename In::value_type> v(begin, end);
                std::sort(v.begin(), v.end(), comp);
                std::copy(v.rbegin(), v.rbegin() + x, out);
                std::advance(out, x);
            } else {
                // accept all peaks
                std::copy(begin, end, out);
                std::advance(out, size);
            }
            return out;
        }

        static const bool registerLoader()
        {
            std::string ids = "TopXInWindowsOfSizeZAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                TopXInWindowsOfSizeZAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool TopXInWindowsOfSizeZAlgorithm::registered_ = registerLoader();
}

#endif /* TOPXINWINDOWSOFSIZEZALGORITHM_HPP_ */
