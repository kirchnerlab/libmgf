INCLUDE_DIRECTORIES(
    ${MGF_SOURCE_DIR}/include
    ${MGF_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(MGF_SRCS
   Driver.cpp
   Parser.cpp
   Scanner.cpp
   MgfHeader.cpp
   MgfSpectrum.cpp
   MgfFile.cpp
)

ADD_LIBRARY(mgf ${MGF_SRCS})

INSTALL(TARGETS mgf 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        COMPONENT libraries)

