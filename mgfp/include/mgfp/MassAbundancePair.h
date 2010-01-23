#ifndef __MASSABUNDANCEPAIR_H__
#define __MASSABUNDANCEPAIR_H__

#include <mgfp/config.h>

#include <utility>
#include <functional>

namespace mgf {

typedef std::pair<double, double> MassAbundancePair;

struct LessThanMass :  std::binary_function<bool, MassAbundancePair, MassAbundancePair> {
    bool operator()(const MassAbundancePair& lhs, const MassAbundancePair& rhs) {
        return lhs.first < rhs.first;
    }
    bool operator()(const double lhs, const MassAbundancePair& rhs) {
        return lhs < rhs.first;
    }
    bool operator()(const MassAbundancePair& lhs, const double rhs) {
        return lhs.first < rhs;
    }
};

struct LessThanAbundance :  std::binary_function<bool, MassAbundancePair, MassAbundancePair> {
    bool operator()(const MassAbundancePair& lhs, const MassAbundancePair& rhs) {
        return lhs.second < rhs.second;
    }
};

} // namespace mgf

#endif

