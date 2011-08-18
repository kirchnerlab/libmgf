// $Id$
#ifndef __MGFP_INCLUDE_CONTEXT_H__
#define __MGFP_INCLUDE_CONTEXT_H__

#include <mgfp/MgfFile.h>
#include <mgfp/MgfHeader.h>
#include <mgfp/MgfSpectrum.h>

namespace mgf
{

/** Context used to save the parsed expressions. This context is
 * passed along to the Driver class and filled during parsing via bison
 * actions. 
 */
struct MGFP_EXPORT Context
{
    Context(MgfFile& file) : mgfFile(file) {}
    MgfFile& mgfFile;
    MgfSpectrum currentSpectrum;
    MgfHeader header;
};

}

#endif // __MGFP_INCLUDE_CONTEXT_H__
