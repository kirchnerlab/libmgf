INCLUDE_DIRECTORIES(
    ${MGFP_SOURCE_DIR}/include
    ${MGFP_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(MGFP_SRCS
   Driver.cpp
   Parser.cpp
   Scanner.cpp
   MgfHeader.cpp
   MgfSpectrum.cpp
   MgfFile.cpp
)

ADD_LIBRARY(mgfp ${MGFP_SRCS})

