PROJECT(MGFP)

# require at least cmake 2.6
cmake_minimum_required(VERSION 2.6)

# include macro definitions
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros/require_out_of_src_build.cmake)

# require out-of-source build
MACRO_REQUIRE_OUT_OF_SRC_BUILD("MGFp requires out-of-source builds.")

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake 
    ${MGFP_BINARY_DIR}/include/mgfp/config.h
)

# compiler-specific flags
IF(MSVC)
    ADD_DEFINITIONS(/wd4800 /wd4065)
ENDIF(MSVC)

# FIXME: add cmake code to regenerate parser on demand

# add subdirs
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(applications EXCLUDE_FROM_ALL)

