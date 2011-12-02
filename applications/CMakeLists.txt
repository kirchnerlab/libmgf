ADD_SUBDIRECTORY(mgfvalidate)

find_package(Libpipe REQUIRED)
if(LIBPIPE_FOUND AND ENABLE_THREADING)
    ADD_SUBDIRECTORY(ms2preproc_libpipe)
elseif(LIBPIPE_FOUND)
		message(STATUS "ms2preproc_libpipe needs threaded version of libpipe")
else()
    message(STATUS "libpipe missing ms2preproc_libpipe will not be compiled")
endif()

ADD_SUBDIRECTORY(ms2preproc)
ADD_SUBDIRECTORY(rix)

