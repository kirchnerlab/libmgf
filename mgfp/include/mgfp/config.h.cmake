#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef _MSC_VER
	#include "winsock2.h"
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define VERSION @VERSION@

#if defined(WIN32)
    #if defined(mgfp_EXPORTS)
        #define MGFP_EXPORT __declspec( dllexport )
    #else 
        #define MGFP_EXPORT __declspec( dllimport )
    #endif
    /* Disable a template related MSVC warning.
       See: http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html */
    #pragma warning( disable: 4251 )
#else
	#define MGFP_EXPORT
#endif

#endif // __CONFIG_H__

