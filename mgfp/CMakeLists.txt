PROJECT(MGFP)

# require at least cmake 2.6
cmake_minimum_required(VERSION 2.6)

# include macro definitions
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros/require_out_of_src_build.cmake)

#############################################################################
# versioning
#############################################################################
set(VERSION_MAJOR 1)
set(VERSION_MINOR 2)

# get SVN revision
EXECUTE_PROCESS(
    COMMAND "svnversion"
    WORKING_DIRECTORY ${MGFP_SOURCE_DIR}
    RESULT_VARIABLE svnversion_failed
    OUTPUT_VARIABLE SVNVERSION
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
IF(svnversion_failed)
    SET(SVNVERSIONSTR "r0")
ELSE(svnversion_failed)
    SET(SVNVERSIONSTR "r${SVNVERSION}")
ENDIF(svnversion_failed)

# construct version string
STRING(REGEX REPLACE ":" "_" VERSION_PATCH ${SVNVERSIONSTR})
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#############################################################################
# build
#############################################################################

# require out-of-source build
MACRO_REQUIRE_OUT_OF_SRC_BUILD("MGFp requires out-of-source builds.")

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mgfp/config.h.cmake 
    ${MGFP_BINARY_DIR}/include/mgfp/config.h
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
CONFIGURE_FILE(${MGFP_SOURCE_DIR}/doc/Doxyfile.cmake
    ${MGFP_BINARY_DIR}/doc/Doxyfile
    @ONLY IMMEDIATE
)
FIND_PACKAGE(Doxygen)
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN} ${MGFP_BINARY_DIR}/doc/Doxyfile)

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
INSTALL(DIRECTORY ${MGFP_SOURCE_DIR}/include/mgfp
        DESTINATION include
	COMPONENT headers
        REGEX "/.svn$" EXCLUDE)

# config.h
INSTALL(FILES ${MGFP_BINARY_DIR}/include/mgfp/config.h
        DESTINATION include/mgfp
	COMPONENT headers)

# documentation
INSTALL(DIRECTORY ${MGFP_BINARY_DIR}/doc
        DESTINATION share/mgfp
	COMPONENT documentation
        PATTERN "Doxyfile" EXCLUDE)

#############################################################################
# packaging
#############################################################################

set(CPACK_PACKAGE_NAME "mgfp")
set(CPACK_PACKAGE_VENDOR "steenlab.org")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MGF Parser")


# CPack version strings
SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

SET(CPACK_RESOURCE_FILE_README "${MGFP_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${MGFP_SOURCE_DIR}/LICENSE.txt")

set(CPACK_COMPONENTS_ALL libraries headers applications documentation)
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "MGFp Applications")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Development Headers")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "C++ Interface Documentation")

set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION 
   "A simple MGF validator.")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
   "Static libraries necessary used to build programs with MGFp.")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
   "C++ header files for MGFp development.")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
   "The C++ MGFp interface documentation (Doxygen).")

INCLUDE(CPack)

