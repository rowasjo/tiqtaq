cmake_minimum_required(VERSION 3.16)

include(CMakePrintHelpers)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(ROW_TiqTaq VERSION 0.1.0 LANGUAGES CXX)
message(STATUS "Configuring project ${CMAKE_PROJECT_NAME} ...")
enable_testing()

include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "" OFF)

if(NOT APPLE)
  set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

add_subdirectory(tiqtaqcore)
add_subdirectory(tiqtaq)

include(CTest)
if(BUILD_TESTING)
  message(STATUS "Configuring ${CMAKE_PROJECT_NAME} tests ...")

  include(FetchContent)
  FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11)

  FetchContent_MakeAvailable(doctest)

  list(APPEND CMAKE_MODULE_PATH ${doctest_SOURCE_DIR}/scripts/cmake)

  add_subdirectory(tests)
endif()

add_subdirectory(exports)

# Only include packaging if we are the top level project
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  include(ROW_TiqTaq/packaging)
endif()
