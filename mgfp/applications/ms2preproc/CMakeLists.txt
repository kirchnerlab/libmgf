#############################################################################
# make sure we find the headers
#############################################################################
INCLUDE_DIRECTORIES(
    ${MGFP_SOURCE_DIR}/include
    ${MGFP_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
#############################################################################
# require boost
#############################################################################
IF(MSVC) 
    SET(Boost_USE_STATIC_LIBS ON)
    SET(Boost_USE_MULTITHREAD OFF)
ENDIF(MSVC)
FIND_PACKAGE(Boost COMPONENTS program_options)
IF(Boost_PROGRAM_OPTIONS_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    SET(SRCS_MS2PREPROC ms2preproc.cpp)
    ADD_EXECUTABLE(ms2preproc ${SRCS_MS2PREPROC})
    TARGET_LINK_LIBRARIES(ms2preproc mgfp ${Boost_PROGRAM_OPTIONS_LIBRARY})
    INSTALL(TARGETS ms2preproc RUNTIME 
	DESTINATION bin
	COMPONENT applications)
ELSE(Boost_PROGRAM_OPTIONS_FOUND)
    MESSAGE(STATUS "Could not find BOOST program_options. Skipping ${CMAKE_CURRENT_SOURCE_DIR}.") 
ENDIF(Boost_PROGRAM_OPTIONS_FOUND)

