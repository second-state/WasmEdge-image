// SPDX-License-Identifier: Apache-2.0
#include <ssvm.h>

#include "image_module.h"

#ifdef __cplusplus
extern "C" {
#endif

SSVM_ImportObjectContext *SSVM_Image_ImportObjectCreate() {
  return reinterpret_cast<SSVM_ImportObjectContext *>(
      new SSVM::Host::SSVMImageModule());
}

#ifdef __cplusplus
} /// extern "C"
#endif
