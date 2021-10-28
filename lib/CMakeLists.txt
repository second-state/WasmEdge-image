# SPDX-License-Identifier: Apache-2.0

find_package(Boost QUIET)

add_library(wasmedgeHostModuleWasmEdgeImage
  image_module.cpp
  image_func.cpp
)

target_link_libraries(wasmedgeHostModuleWasmEdgeImage
  PUBLIC
  wasmedgeCommon
  wasmedgeSystem
  Boost::boost
  ${JPEG_LIB}
  ${PNG_LIB}
  ${ZLIB_LIBRARIES}
)

target_include_directories(wasmedgeHostModuleWasmEdgeImage
  PUBLIC
  ${JPEG_INCLUDE}
  ${PNG_INCLUDE}
  ${WASMEDGE_CORE_PATH}/include
)

if (WASMEDGE_IMAGE_BUILD_SHARED_LIB)
  add_library(wasmedge-image_c SHARED
    wasmedge-image.cpp
    image_module.cpp
    image_func.cpp
  )

  target_link_libraries(wasmedge-image_c
    PUBLIC
    wasmedgeCommon
    wasmedgeSystem
    Boost::boost
    ${JPEG_LIB}
    ${PNG_LIB}
    ${ZLIB_LIBRARIES}
  )

  target_include_directories(wasmedge-image_c
    PUBLIC
    ${JPEG_INCLUDE}
    ${PNG_INCLUDE}
    ${WASMEDGE_CORE_PATH}/include
    ${WASMEDGE_CORE_BIN_PATH}/include/api
  )
endif()
