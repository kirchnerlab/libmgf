#ifndef __UTILS_H__
#define __UTILS_H__

#include <mgfp/config.h>

namespace mgf
{

template <class T>
typename T::mapped_type existsOrEmpty(T map, typename T::key_type key)
{
    typename T::iterator i = map.find(key);
    if (i != map.end()) {
        return i->second;
    }
    else {
        return typename T::mapped_type();
    }
}

}

#endif

