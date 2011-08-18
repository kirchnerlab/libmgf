#############################################################################
# make sure we find the headers
#############################################################################
INCLUDE_DIRECTORIES(
    ${MGF_SOURCE_DIR}/include
    ${MGF_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
#############################################################################
# this requres BOOST
#############################################################################
IF(MSVC) 
    SET(Boost_USE_STATIC_LIBS ON)
    SET(Boost_USE_MULTITHREAD OFF)
ENDIF(MSVC)
FIND_PACKAGE(Boost COMPONENTS program_options)
IF(Boost_PROGRAM_OPTIONS_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    SET(SRCS_MGFVALIDATE mgfvalidate.cpp)
    ADD_EXECUTABLE(mgfvalidate ${SRCS_MGFVALIDATE})
    TARGET_LINK_LIBRARIES(mgfvalidate mgf ${Boost_PROGRAM_OPTIONS_LIBRARY})
    INSTALL(TARGETS mgfvalidate RUNTIME 
        DESTINATION bin
        COMPONENT applications)
ELSE(Boost_PROGRAM_OPTIONS_FOUND)
    MESSAGE(STATUS "Could not find BOOST program_options. Skipping ${CMAKE_CURRENT_SOURCE_DIR}.") 
ENDIF(Boost_PROGRAM_OPTIONS_FOUND)

