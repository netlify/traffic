include(FindPackageHandleStandardArgs)

find_library(TrafficServer_Management_LIBRARY NAMES tsmgmt PATH_SUFFIXES trafficserver)
find_library(TrafficServer_Config_LIBRARY NAMES tsconfig PATH_SUFFIXES trafficserver)
find_library(TrafficServer_CXX_LIBRARY NAMES tscppapi atscppapi PATH_SUFFIXES trafficserver)
find_library(TrafficServer_LIBRARY NAMES tscore PATH_SUFFIXES trafficserver)

find_path(TrafficServer_Management_INCLUDE_DIR NAMES ts/mgmtapi.h)
find_path(TrafficServer_Config_INCLUDE_DIR NAMES ts/ts.h)
find_path(TrafficServer_CXX_INCLUDE_DIR NAMES tscpp/api/Async.h atscppapi/Async.h)
find_path(TrafficServer_INCLUDE_DIR NAMES ts/ts.h)

find_program(TrafficServer_Control_EXECUTABLE NAMES traffic_ctl)

if (TrafficServer_Control_EXECUTABLE AND NOT TrafficServer_VERSION)
  execute_process(
    COMMAND ${TrafficServer_Control_EXECUTABLE} --version
    OUTPUT_VARIABLE TrafficServer_Control_VERSION_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ENCODING UTF-8)
  if (TrafficServer_Control_VERSION_OUTPUT)
    string(REGEX
      MATCH "[^0-9]+([0-9]+)[.]([0-9]+)?[.]?([0-9]+)?[.]?([0-9]+)?.*"
      TrafficServer_VERSION_CHECK
      ${TrafficServer_Control_VERSION_OUTPUT})
    if (TrafficServer_VERSION_CHECK)
      string(JOIN "." TrafficServer_VERSION
        ${CMAKE_MATCH_1}
        ${CMAKE_MATCH_2}
        ${CMAKE_MATCH_3}
        ${CMAKE_MATCH_4})
      set(TrafficServer_VERSION "${TrafficServer_VERSION}" CACHE STRING "TrafficServer Version" FORCE)
    endif()
  endif()
endif()

if (TrafficServer_Control_EXECUTABLE)
  set(TrafficServer_Control_FOUND YES)
endif()

if (TrafficServer_Management_LIBRARY AND TrafficServer_Management_INCLUDE_DIR)
  set(TrafficServer_Management_FOUND YES)
endif()

if (TrafficServer_Config_LIBRARY AND TrafficServer_Config_INCLUDE_DIR)
  set(TrafficServer_Config_FOUND YES)
endif()

if (TrafficServer_CXX_LIBRARY AND TrafficServer_CXX_INCLUDE_DIR)
  set(TrafficServer_CXX_FOUND YES)
endif()

if (TrafficServer_LIBRARY AND TrafficServer_INCLUDE_DIR)
  set(TrafficServer_Core_FOUND YES)
endif()

find_package_handle_standard_args(TrafficServer
  REQUIRED_VARS TrafficServer_LIBRARY TrafficServer_INCLUDE_DIR
  VERSION_VAR TrafficServer_VERSION
  HANDLE_COMPONENTS)

if (TrafficServer_Core_FOUND AND NOT TARGET TrafficServer::Core)
  add_library(TrafficServer::Core IMPORTED UNKNOWN)
  target_include_directories(TrafficServer::Core INTERFACE ${TrafficServer_INCLUDE_DIR})
  set_property(TARGET TrafficServer::Core
    PROPERTY
      IMPORTED_LOCATION ${TrafficServer_LIBRARY})
endif()

if (TrafficServer_Management_FOUND AND NOT TARGET TrafficServer::Management)
  add_library(TrafficServer::Management IMPORTED UNKNOWN)
  target_include_directories(TrafficServer::Management INTERFACE ${TrafficServer_Management_INCLUDE_DIR})
  set_property(TARGET TrafficServer::Management
    PROPERTY
    IMPORTED_LOCATION ${TrafficServer_Management_LIBRARY})
endif()

if (TrafficServer_Config_FOUND AND NOT TARGET TrafficServer::Config)
  add_library(TrafficServer::Config IMPORTED UNKNOWN)
  target_include_directories(TrafficServer::Config INTERFACE ${TrafficServer_Config_INCLUDE_DIR})
  set_property(TARGET TrafficServer::Config
    PROPERTY
    IMPORTED_LOCATION ${TrafficServer_Config_LIBRARY})
endif()

if (TrafficServer_CXX_FOUND AND NOT TARGET TrafficServer::CXX)
  add_library(TrafficServer::CXX IMPORTED UNKNOWN)
  target_include_directories(TrafficServer::CXX INTERFACE ${TrafficServer_CXX_INCLUDE_DIR})
  set_property(TARGET TrafficServer::CXX
    PROPERTY
    IMPORTED_LOCATION ${TrafficServer_CXX_LIBRARY})
endif()
