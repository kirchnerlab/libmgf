/*
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

#ifndef __MS2PREPROC_LIBPIPE_UTIL_HPP_
#define __MS2PREPROC_LIBPIPE_UTIL_HPP_

#include <mgf/Context.h>


struct LessThanMass
{
        bool operator()(const mgf::MassAbundancePair& lhs,
            const mgf::MassAbundancePair& rhs)
        {
            return lhs.first < rhs.first;
        }
        bool operator()(const double lhs, const mgf::MassAbundancePair& rhs)
        {
            return lhs < rhs.first;
        }
        bool operator()(const mgf::MassAbundancePair& lhs, const double rhs)
        {
            return lhs.first < rhs;
        }
};

struct LessThanAbundance
{
        bool operator()(const mgf::MassAbundancePair& lhs,
            const mgf::MassAbundancePair& rhs)
        {
            return lhs.second < rhs.second;
        }
        bool operator()(const double lhs, const mgf::MassAbundancePair& rhs)
        {
            return lhs < rhs.second;
        }
        bool operator()(const mgf::MassAbundancePair& lhs, const double rhs)
        {
            return lhs.second < rhs;
        }
};


#endif /* __MS2PREPROC_LIBPIPE_UTIL_HPP_ */
