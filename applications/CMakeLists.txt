ADD_SUBDIRECTORY(mgfvalidate)

find_package(Libpipe REQUIRED)
if(LIBPIPE_FOUND)
    ADD_SUBDIRECTORY(ms2preproc)
else()
    message(STATUS "libpipe missing ms2preproc will not be compiled")
endif()


ADD_SUBDIRECTORY(rix)

