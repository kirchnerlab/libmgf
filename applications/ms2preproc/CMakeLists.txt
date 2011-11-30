#############################################################################
# make sure we find the headers
#############################################################################
INCLUDE_DIRECTORIES(
    ${MGF_SOURCE_DIR}/include
    ${MGF_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#############################################################################
# require boost and libpipe
#############################################################################
IF(MSVC)
    SET(Boost_USE_STATIC_LIBS ON)
    SET(Boost_USE_MULTITHREAD OFF)
ENDIF(MSVC)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
IF(Boost_PROGRAM_OPTIONS_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    INCLUDE_DIRECTORIES(${LIBPIPE_INCLUDE_DIR})
    SET(SRCS_MS2PREPROC ms2preproc.cpp)
    ADD_EXECUTABLE(ms2preproc ${SRCS_MS2PREPROC})

    SET(LINK_LIBS
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${LIBPIPE_LIBRARIES}
    )
    TARGET_LINK_LIBRARIES(ms2preproc mgf ${LINK_LIBS})
    INSTALL(TARGETS ms2preproc RUNTIME
    DESTINATION bin
    COMPONENT applications)
ELSE(Boost_PROGRAM_OPTIONS_FOUND)
    MESSAGE(STATUS "Could not find BOOST program_options. Skipping ${CMAKE_CURRENT_SOURCE_DIR}.")
ENDIF(Boost_PROGRAM_OPTIONS_FOUND)

CONFIGURE_FILE(${MGF_SOURCE_DIR}/applications/ms2preproc/inputFileFilterJSON.txt.cmake
    ${MGF_BINARY_DIR}/applications/ms2preproc/inputFileFilterJSON.txt
    @ONLY IMMEDIATE
    )
    
CONFIGURE_FILE(${MGF_SOURCE_DIR}/applications/ms2preproc/inputFilePipelineJSON.txt.cmake
    ${MGF_BINARY_DIR}/applications/ms2preproc/inputFilePipelineJSON.txt
    @ONLY IMMEDIATE
    )        
    
CONFIGURE_FILE(${MGF_SOURCE_DIR}/applications/ms2preproc/inputFileConnectionJSON.txt.cmake
    ${MGF_BINARY_DIR}/applications/ms2preproc/inputFileConnectionJSON.txt
    @ONLY IMMEDIATE
    )
    
CONFIGURE_FILE(${MGF_SOURCE_DIR}/applications/ms2preproc/inputFileParametersJSON.txt.cmake
    ${MGF_BINARY_DIR}/applications/ms2preproc/inputFileParametersJSON.txt
    @ONLY IMMEDIATE
    )  
        


