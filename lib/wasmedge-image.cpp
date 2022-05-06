// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "wasmedge/wasmedge-image.h"
#include "image_module.h"

#ifdef __cplusplus
extern "C" {
#endif

WasmEdge_ModuleInstanceContext *WasmEdge_Image_ModuleInstanceCreate() {
  return reinterpret_cast<WasmEdge_ModuleInstanceContext *>(
      new WasmEdge::Host::WasmEdgeImageModule());
}

#ifdef __cplusplus
} // extern "C"
#endif
