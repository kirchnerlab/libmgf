PROJECT(MGF)

# require at least cmake 2.6
cmake_minimum_required(VERSION 2.6)

# include macro definitions
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros/require_out_of_src_build.cmake)

#############################################################################
# versioning
#############################################################################
set(VERSION_MAJOR 2)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#############################################################################
# build
#############################################################################

# require out-of-source build
MACRO_REQUIRE_OUT_OF_SRC_BUILD("libmgf requires out-of-source builds.")

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mgfp/config.h.cmake 
    ${MGF_BINARY_DIR}/include/mgfp/config.h
)

# compiler-specific flags
IF(MSVC)
    ADD_DEFINITIONS(/wd4800 /wd4065)
ENDIF(MSVC)

# FIXME: add cmake code to regenerate parser on demand

# add subdirs
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(applications)

# doxygen support
CONFIGURE_FILE(${MGF_SOURCE_DIR}/doc/Doxyfile.cmake
    ${MGF_BINARY_DIR}/doc/Doxyfile
    @ONLY IMMEDIATE
)
FIND_PACKAGE(Doxygen)

# target for doxygen
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN} ${MGF_BINARY_DIR}/doc/Doxyfile)

#############################################################################
# regression tests
#############################################################################
INCLUDE(CTest)
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)

#############################################################################
# installation
#############################################################################

# headers
INSTALL(DIRECTORY ${MGF_SOURCE_DIR}/include/mgfp
        DESTINATION include
        COMPONENT headers
        REGEX "/.svn$" EXCLUDE)

# config.h
INSTALL(FILES ${MGF_BINARY_DIR}/include/mgfp/config.h
        DESTINATION include/mgfp
        COMPONENT headers)

# documentation
INSTALL(DIRECTORY ${MGF_BINARY_DIR}/doc
        DESTINATION share/mgfp
        COMPONENT documentation
        PATTERN "Doxyfile" EXCLUDE)

#############################################################################
# packaging
#############################################################################

# FIXME: make sure that the documentation is compiled and pdfs are 
#        generated prior to packaging!

set(CPACK_PACKAGE_NAME "libmgf")
set(CPACK_PACKAGE_VENDOR "https://github.com/mkirchner/libmgf")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MGF Parser Library")


# CPack version strings
SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

SET(CPACK_RESOURCE_FILE_README "${MGF_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${MGF_SOURCE_DIR}/LICENSE.txt")

set(CPACK_COMPONENTS_ALL libraries headers applications documentation)
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "MGFp Applications")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Development Headers")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "C++ Interface Documentation")

set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION 
   "A simple MGF validator, TMT/iTRAQ reporter ion extraction and MGF preprocessing tools.")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
   "Static libraries necessary used to build programs with MGFp.")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
   "C++ header files for libmgf development.")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
   "The C++ libmgf interface documentation (Doxygen).")

INCLUDE(CPack)

