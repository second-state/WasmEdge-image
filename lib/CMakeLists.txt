# SPDX-License-Identifier: Apache-2.0

add_library(ssvmHostModuleSSVMImage
  image_module.cpp
  image_func.cpp
)

target_link_libraries(ssvmHostModuleSSVMImage
  PRIVATE
  ${JPEG_LIB}
  ${PNG_LIB}
  ${ZLIB_LIBRARIES}
)

target_include_directories(ssvmHostModuleSSVMImage
  PUBLIC
  ${JPEG_INCLUDE}
  ${PNG_INCLUDE}
  ${Boost_INCLUDE_DIR}
  ${SSVM_CORE_PATH}/include
  ${SSVM_CORE_PATH}/thirdparty
)

add_library(ssvm-image_c SHARED
  ssvm-image.cpp
  image_module.cpp
  image_func.cpp
)

target_link_libraries(ssvm-image_c
  PUBLIC
  ${ZLIB_LIBRARIES}
)

target_include_directories(ssvm-image_c
  PUBLIC
  ${JPEG_INCLUDE}
  ${PNG_INCLUDE}
  ${Boost_INCLUDE_DIR}
  ${SSVM_CORE_PATH}/include
  ${SSVM_CORE_PATH}/thirdparty
  ${SSVM_CORE_BIN_PATH}/include/api
)
