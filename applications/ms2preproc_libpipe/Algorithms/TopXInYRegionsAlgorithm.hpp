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

#ifndef TOPXINYREGIONSALGORITHM_HPP_
#define TOPXINYREGIONSALGORITHM_HPP_

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

class TopXInYRegionsAlgorithm : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new TopXInYRegionsAlgorithm;
        }

        virtual ~TopXInYRegionsAlgorithm()
        {
        }

        void update(libpipe::Request& req)
        {

            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfInputFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFInputFile"));
            boost::shared_ptr<libpipe::rtc::SharedData<mgf::MgfFile> > mgfParsedFile =
                    boost::dynamic_pointer_cast<
                            libpipe::rtc::SharedData<mgf::MgfFile> >(
                        this->getPort("MGFParsedFile"));
            LIBPIPE_PIPELINE_TRACE(req, "Starting TopXInYRegions");

            mgfInputFile->shared_lock();
            mgfParsedFile->lock();
            // copy the file so that input is not changed.
            mgfParsedFile->set(new mgf::MgfFile(*mgfInputFile->get()));
            mgfInputFile->unlock();

            // Top X in Y regions

            for (mgf::MgfFile::iterator i = mgfParsedFile->get()->begin();
                    i != mgfParsedFile->get()->end(); ++i) {
                // get a temporary object and make sure it is big enough
                mgf::MgfSpectrum m;
                m.resize(2 * i->size());
                // get the top X in Y regions, including duplicated from overlaps
                mgf::MgfSpectrum::iterator sEnd = run(i->begin(), i->end(),
                    m.begin(), LessThanMass(), LessThanAbundance());
                // make sure we have enough space in the original object
                i->resize(std::distance(m.begin(), sEnd));
                // unique copy expectes a sorted range
                std::sort(m.begin(), sEnd, LessThanMass());
                // copy all unique peaks back into the original MgfSpectrum
                mgf::MgfSpectrum::iterator iEnd = std::unique_copy(m.begin(),
                    sEnd, i->begin());
                // crop to fit
                i->resize(std::distance(i->begin(), iEnd));
            }

            mgfParsedFile->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "TopXInYRegions is finished");

        }

    protected:

    private:
        TopXInYRegionsAlgorithm() :
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
            // sort a copy
            std::vector<typename In::value_type> v(begin, end);
            std::sort(v.begin(), v.end(), massComp);
            // split the m/z domain in y_ equisized regions
            double maxMz = (v.end() - 1)->first;
            double minMz = (v.begin())->first;
            double increment = (maxMz - minMz)
                    / static_cast<double>(parameters_.get<unsigned int>(
                        "nregions"));
            if (increment > 2.5) {
                for (unsigned int k = 0;
                        k < parameters_.get<unsigned int>("nregions"); ++k) {
                    // iterate over all regions and apply TopX
                    double regionBegin = minMz + k * increment - 2.5;
                    regionBegin = regionBegin > minMz ? regionBegin : minMz;
                    double regionEnd = minMz + (k + 1) * increment + 2.5;
                    In regionBeginIt = std::lower_bound(v.begin(), v.end(),
                        regionBegin, massComp);
                    In regionEndIt = std::upper_bound(v.begin(), v.end(),
                        regionEnd, massComp);
                    // run TopX on region
                    Out nout = runTopX(regionBeginIt, regionEndIt, out,
                        abundanceComp);
                    out = nout;

                }
            } else {
                Out nout = runTopX(v.begin(), v.end(), out, abundanceComp);
                out = nout;
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
            std::string ids = "TopXInYRegionsAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                TopXInYRegionsAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool TopXInYRegionsAlgorithm::registered_ = registerLoader();
}

#endif /* TOPXINYREGIONSALGORITHM_HPP_ */
