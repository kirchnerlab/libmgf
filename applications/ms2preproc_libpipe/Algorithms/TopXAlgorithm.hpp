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

#ifndef TOPXALGORITHM_HPP_
#define TOPXALGORITHM_HPP_

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


class TopXAlgorithm : public libpipe::rtc::Algorithm
{

    public:
        static libpipe::rtc::Algorithm* create()
        {
            return new TopXAlgorithm;
        }

        virtual ~TopXAlgorithm()
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
            LIBPIPE_PIPELINE_TRACE(req, "Starting TopX");

            mgfInputFile->shared_lock();
            mgfParsedFile->lock();
            // copy the file so that input is not changed.
            mgfParsedFile->set(new mgf::MgfFile(*mgfInputFile->get()));
            mgfInputFile->unlock();

            for (mgf::MgfFile::iterator i = mgfParsedFile->get()->begin();
                    i != mgfParsedFile->get()->end(); ++i) {
                mgf::MgfSpectrum::iterator trash = run(i->begin(), i->end(),
                    i->begin(), LessThanAbundance());
                i->erase(trash, i->end());
                std::sort(i->begin(), i->end(), LessThanMass());
            }

            mgfParsedFile->unlock();

            LIBPIPE_PIPELINE_TRACE(req, "TopX is finished");

        }

    protected:

    private:
        TopXAlgorithm() :
                libpipe::rtc::Algorithm()
        {
            ports_["MGFInputFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >();
            ports_["MGFParsedFile"] = boost::make_shared<
                    libpipe::rtc::SharedData<mgf::MgfFile> >(new mgf::MgfFile);
        }

        template<class In, class Out, class Comp>
        Out run(In begin, In end, Out out, Comp comp)
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
            std::string ids = "TopXAlgorithm";
            return libpipe::rtc::AlgorithmFactory::instance().registerType(ids,
                TopXAlgorithm::create);
        }
        /// true is class is registered in Algorithm Factory
        static const bool registered_;
};
const bool TopXAlgorithm::registered_ = registerLoader();
}

#endif /* TOPXALGORITHM_HPP_ */
