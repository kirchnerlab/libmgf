PROJECT(MGFP)

# require at least cmake 2.6
cmake_minimum_required(VERSION 2.6)

# include macro definitions
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros/require_out_of_src_build.cmake)

#############################################################################
# build
#############################################################################

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

# doxygen support
CONFIGURE_FILE(${MGFP_SOURCE_DIR}/Doxyfile.cmake
    ${MGFP_BINARY_DIR}/doc/Doxyfile
    @ONLY IMMEDIATE
)
FIND_PACKAGE(Doxygen)
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN} ${MGFP_BINARY_DIR}/doc/Doxyfile)

#############################################################################
# installation
#############################################################################

# headers
INSTALL(DIRECTORY ${MGFP_SOURCE_DIR}/include/mgfp
        DESTINATION include
        REGEX "/.svn$" EXCLUDE)

# config.h
INSTALL(FILES ${MGFP_BINARY_DIR}/include/mgfp/config.h
        DESTINATION include/mgfp)

# documentation
INSTALL(DIRECTORY ${MGFP_BINARY_DIR}/doc
        DESTINATION share/mgfp
        PATTERN "Doxyfile" EXCLUDE)

