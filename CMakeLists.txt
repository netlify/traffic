cmake_minimum_required(VERSION 3.16)
include(FetchContent)
FetchContent_Declare(cmake GIT_REPOSITORY https://github.com/netlify/cmake GIT_TAG main)
FetchContent_MakeAvailable(cmake)
set(CMAKE_PROJECT_INCLUDE ${NETLIFY_PROJECT_PRELUDE})
project(traffic
  LANGUAGES CXX
  VERSION 0.1.0)

FetchContent_Declare(aegis GIT_REPOSITORY https://github.com/netlify/aegis GIT_TAG main)
FetchContent_Declare(apex GIT_REPOSITORY https://github.com/netlify/apex GIT_TAG main)
FetchContent_MakeAvailable(apex aegis)

find_package(TrafficServer REQUIRED)

add_library(${PROJECT_NAME})
add_library(netlify::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cxx")
target_sources(${PROJECT_NAME} PRIVATE ${sources})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME}
  PRIVATE
    ${--warn-thread-safety}
    ${--warn-unused-variable}
    ${--warn-strict-aliasing}
    ${--warn-uninitialized}
    ${--warn-useless-cast}
    ${--warn-cast-align}
    ${--warn-format-2}
    ${--warn-pedantic}
    ${--warn-default}
    ${--warn-extra})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src>)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    TrafficServer::Core
    netlify::aegis
    netlify::apex)

install(TARGETS traffic
  EXPORT netlify-traffic
  ARCHIVE COMPONENT Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT netlify-traffic
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/netlify-traffic
  COMPONENT Development
  NAMESPACE netlify::)
install(DIRECTORY include/
  TYPE INCLUDE
  COMPONENT Development
  FILES_MATCHING
    PATTERN "*.hpp")

set_property(TARGET sphinx::traffic PROPERTY SPHINX_GITHUB_USER "netlify")
set_property(TARGET sphinx::traffic PROPERTY SPHINX_GITHUB_REPO "traffic")

set_property(TARGET sphinx::traffic PROPERTY SPHINX_PROJECT_COPYRIGHT "Netlify Inc")
set_property(TARGET sphinx::traffic PROPERTY SPHINX_PROJECT_NAME "Netlify Traffic")

set_property(TARGET sphinx::traffic PROPERTY SPHINX_CONSOLE_COLOR ON)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  feature_summary(DEFAULT_DESCRIPTION WHAT ALL)
endif()
