// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "image_module.h"
#include "image_func.h"

#include <memory>

namespace WasmEdge {
namespace Host {

WasmEdgeImageModule::WasmEdgeImageModule()
    : Runtime::Instance::ModuleInstance("wasmedge_image") {
  addHostFunc("wasmedge_image_load_jpg_to_rgb8",
              std::make_unique<WasmEdgeImageLoadJPGToRGB8>());
  addHostFunc("wasmedge_image_load_jpg_to_bgr8",
              std::make_unique<WasmEdgeImageLoadJPGToBGR8>());
  addHostFunc("wasmedge_image_load_jpg_to_rgb32f",
              std::make_unique<WasmEdgeImageLoadJPGToRGB32F>());
  addHostFunc("wasmedge_image_load_jpg_to_bgr32f",
              std::make_unique<WasmEdgeImageLoadJPGToBGR32F>());
  addHostFunc("wasmedge_image_load_png_to_rgb8",
              std::make_unique<WasmEdgeImageLoadPNGToRGB8>());
  addHostFunc("wasmedge_image_load_png_to_bgr8",
              std::make_unique<WasmEdgeImageLoadPNGToBGR8>());
  addHostFunc("wasmedge_image_load_png_to_rgb32f",
              std::make_unique<WasmEdgeImageLoadPNGToRGB32F>());
  addHostFunc("wasmedge_image_load_png_to_bgr32f",
              std::make_unique<WasmEdgeImageLoadPNGToBGR32F>());
  addHostFunc("wasmedge_image_load_jpg_to_luma",
              std::make_unique<WasmedgeImageLoadJPGToLuma>());
}

} // namespace Host
} // namespace WasmEdge
