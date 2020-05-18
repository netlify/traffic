include(FindPackageHandleStandardArgs)

find_program(SCCache_EXECUTABLE NAMES sccache)

if (SCCache_EXECUTABLE AND NOT SCCache_VERSION)
  execute_process(
    COMMAND ${SCCache_EXECUTABLE} --version
    OUTPUT_VARIABLE SCCache_VERSION_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ENCODING UTF-8)
  if (SCCache_VERSION_OUTPUT)
    string(REGEX
      MATCH "[^0-9]+([0-9]+)[.]([0-9]+)?[.]?([0-9]+)?[.]?([0-9]+)?.*"
      SCCache_VERSION_CHECK
      ${SCCache_VERSION_OUTPUT})
    if (SCCache_VERSION_CHECK)
      string(JOIN "." SCCache_VERSION
        ${CMAKE_MATCH_1}
        ${CMAKE_MATCH_2}
        ${CMAKE_MATCH_3}
        ${CMAKE_MATCH_4})
      set(SCCache_VERSION "${SCCache_VERSION}" CACHE STRING "SCCache Version" FORCE)
    endif()
  endif()
endif()

find_package_handle_standard_args(SCCache
  REQUIRED_VARS SCCache_EXECUTABLE
  VERSION_VAR SCCache_VERSION)

if (SCCache_FOUND AND NOT TARGET SCCache::SCCache)
  add_executable(SCCache::SCCache IMPORTED)
  set_property(TARGET SCCache::SCCache
    PROPERTY
      IMPORTED_LOCATION ${SCCache_EXECUTABLE})
endif()
