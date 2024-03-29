# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

cmake_minimum_required(VERSION 3.11)
project(WasmEdge-Image)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  if (CMAKE_GENERATOR STREQUAL Ninja)
    if(CMAKE_COMPILER_IS_GNUCXX)
      list(TRANSFORM CMAKE_C_COMPILE_OPTIONS_IPO REPLACE "^-flto$" "-flto=auto")
      list(TRANSFORM CMAKE_CXX_COMPILE_OPTIONS_IPO REPLACE "^-flto$" "-flto=auto")
    endif()
    set(CMAKE_JOB_POOLS "link=2")
    set(CMAKE_JOB_POOL_LINK link)
  endif()
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_SKIP_RPATH ON)

# List of WasmEdge options
option(WASMEDGE_BUILD_TOOLS "Generate wasmedge and wasmedgec tools." OFF)
# Libraries will be built in this project, hence the wasmedge and wasmedgec are not needed.
option(WASMEDGE_BUILD_AOT_RUNTIME "Enable WasmEdge LLVM-based ahead of time compilation runtime." OFF)
# AOT runtime is not needed in this stand-alone project.
option(WASMEDGE_BUILD_SHARED_LIB "Generate the WasmEdge shared library." OFF)
# libwasmedge_c.so is not needed in this stand-alone project.
option(WASMEDGE_IMAGE_BUILD_SHARED_LIB "Generate the libwasmedge-image_c shared library." ON)

# WasmEdge repositories versions
if(NOT WASMEDGE_REPO_VERSION)
  set(WASMEDGE_REPO_VERSION "0.13.0-alpha.1")
endif()

find_package(ZLIB REQUIRED)
find_package(Boost 1.74.0)
if(${Boost_FOUND})
else()
  include(FetchContent)
  FetchContent_Declare(
    Boost
    URL https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.bz2
    URL_HASH SHA256=a6e1ab9b0860e6a2881dd7b21fe9f737a095e5f33a3a874afc6a345228597ee6
  )
  set(BOOST_ENABLE_CMAKE ON)
  set(BOOST_RUNTIME_LINK static)
  message(STATUS "Downloading boost 1.82.0 source")
  FetchContent_MakeAvailable(Boost)
  message(STATUS "Downloading boost 1.82.0 source - done")
  add_library(Boost_boost INTERFACE)
  add_library(Boost::boost ALIAS Boost_boost)
  target_include_directories(Boost_boost SYSTEM INTERFACE ${boost_SOURCE_DIR})
endif()

# libjpeg and libpng path
if(ANDROID)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(JPEG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libjpeg_android_aarch64.a)
    set(PNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libpng16_android_aarch64.a)
  elseif()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
elseif(APPLE)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
    set(JPEG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libjpeg_darwin_x86_64.a)
    set(PNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libpng16_darwin_x86_64.a)
  elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(JPEG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libjpeg_darwin_arm64.a)
    set(PNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libpng16_darwin_arm64.a)
  else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
elseif(UNIX)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
    set(JPEG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libjpeg_manylinux2014_x86_64.a)
    set(PNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libpng16_manylinux2014_x86_64.a)
  elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(JPEG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libjpeg_manylinux2014_aarch64.a)
    set(PNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/utils/libpng16_manylinux2014_aarch64.a)
  else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
else()
  message(FATAL_ERROR "Unsupported system: ${CMAKE_SYSTEM_NAME}")
endif()
set(JPEG_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/jpeg
)
set(PNG_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/png
)

# Clone WasmEdge-core
if(NOT WASMEDGE_CORE_PATH)
  include(FetchContent)
  FetchContent_Declare(
    wasmedge
    GIT_REPOSITORY https://github.com/WasmEdge/WasmEdge.git
    GIT_TAG ${WASMEDGE_REPO_VERSION}
  )

  FetchContent_GetProperties(wasmedge)
  if(NOT wasmedge_POPULATED)
    message(STATUS "Fetching WasmEdge repository")
    FetchContent_Populate(wasmedge)
    message(STATUS "Fetching WasmEdge repository - done")
  endif()
  add_subdirectory(${wasmedge_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
  set(WASMEDGE_CORE_PATH ${wasmedge_SOURCE_DIR})
  set(WASMEDGE_CORE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
else()
  get_filename_component(
    WASMEDGE_CORE_PATH "${WASMEDGE_CORE_PATH}"
    REALPATH
    BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  if(NOT WASMEDGE_CORE_BIN_PATH)
    add_subdirectory(${WASMEDGE_CORE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
    set(WASMEDGE_CORE_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/utils/WasmEdge-core)
  else()
    get_filename_component(
      WASMEDGE_CORE_BIN_PATH "${WASMEDGE_CORE_BIN_PATH}"
      REALPATH
      BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  endif()
endif()

message(STATUS "WasmEdge-image: Set WasmEdge-core source path: ${WASMEDGE_CORE_PATH}")
message(STATUS "WasmEdge-image: Set WasmEdge-core binary path: ${WASMEDGE_CORE_BIN_PATH}")

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_subdirectory(include)
add_subdirectory(lib)
