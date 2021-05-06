// SPDX-License-Identifier: Apache-2.0
#include <wasmedge.h>

#include "image_module.h"

#ifdef __cplusplus
extern "C" {
#endif

WasmEdge_ImportObjectContext *WasmEdge_Image_ImportObjectCreate() {
  return reinterpret_cast<WasmEdge_ImportObjectContext *>(
      new WasmEdge::Host::WasmEdgeImageModule());
}

#ifdef __cplusplus
} /// extern "C"
#endif
