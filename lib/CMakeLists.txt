# SPDX-License-Identifier: Apache-2.0

add_library(ssvmHostModuleSSVMImage
  host/image_module.cpp
  host/image_func.cpp
)

target_link_libraries(ssvmHostModuleSSVMImage
  PRIVATE
  ssvmCommon
  ${JPEG_LIB}
  ${PNG_LIB}
)

target_include_directories(ssvmHostModuleSSVMImage
  PUBLIC
  ${JPEG_INCLUDE}
  ${PNG_INCLUDE}
  ${Boost_INCLUDE_DIR}
  ${SSVM_CORE_SRC_DIR}/include
  ${SSVM_CORE_SRC_DIR}/thirdparty
)
