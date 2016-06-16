# - Try to find Zyre
# Once done this will define
#
#  ZYRE_FOUND - system has Zyre
#  ZYRE_INCLUDE_DIR - the Zyre include directory
#  ZYRE_LIBRARY - Link these to use Zyre
#  ZYRE_LIBRARIES - Link these to use Zyre
#

find_package(PkgConfig)
pkg_check_modules(PC_ZYRE libzyre)

find_path(ZYRE_INCLUDE_DIR NAMES zyre.h
  PATHS
    ${PC_ZYRE_INCLUDEDIR}
    ${PC_ZYRE_INCLUDE_DIRS}
    $ENV{ZYRE_HOME}/include
)

find_library(ZYRE_LIBRARY NAMES zyre
  PATHS
    ${PC_ZYRE_LIBDIR}
    ${PC_ZYRE_LIBRARY_DIRS}
    $ENV{ZYRE_HOME}/lib
)

find_library(CZMQ_LIBRARY NAMES czmq
  PATHS
    ${PC_ZYRE_LIBDIR}
    ${PC_ZYRE_LIBRARY_DIRS}
    $ENV{CZMQ_HOME}/lib
)

find_library(ZMQ_LIBRARY NAMES zmq
  PATHS
    ${PC_ZYRE_LIBDIR}
    ${PC_ZYRE_LIBRARY_DIRS}
    $ENV{ZEROMQ_HOME}/lib
)

find_library(SODIUM_LIBRARY NAMES sodium
  PATHS
    ${PC_ZYRE_LIBDIR}
    ${PC_ZYRE_LIBRARY_DIRS}
)

find_library(UUID_LIBRARY NAMES uuid
  PATHS
    ${PC_ZYRE_LIBDIR}
    ${PC_ZYRE_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(zyre  DEFAULT_MSG ZYRE_LIBRARY ZYRE_INCLUDE_DIR)

set(ZYRE_LIBRARIES ${ZYRE_LIBRARY} ${CZMQ_LIBRARY} ${ZMQ_LIBRARY} ${UUID_LIBRARY})

if(SODIUM_LIBRARY)
set(ZYRE_LIBRARIES ${ZYRE_LIBRARIES} ${SODIUM_LIBRARY} )
endif()

mark_as_advanced(ZYRE_INCLUDE_DIR ZYRE_LIBRARY ZYRE_LIBRARIES)
