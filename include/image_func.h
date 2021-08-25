// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "image_base.h"
#include "runtime/hostfunc.h"
#include "runtime/instance/memory.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeImageLoadJPGToRGB8
    : public WasmEdgeImage<WasmEdgeImageLoadJPGToRGB8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class WasmEdgeImageLoadJPGToBGR8
    : public WasmEdgeImage<WasmEdgeImageLoadJPGToBGR8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class WasmEdgeImageLoadJPGToRGB32F
    : public WasmEdgeImage<WasmEdgeImageLoadJPGToRGB32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class WasmEdgeImageLoadJPGToBGR32F
    : public WasmEdgeImage<WasmEdgeImageLoadJPGToBGR32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class WasmEdgeImageLoadPNGToRGB8
    : public WasmEdgeImage<WasmEdgeImageLoadPNGToRGB8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class WasmEdgeImageLoadPNGToBGR8
    : public WasmEdgeImage<WasmEdgeImageLoadPNGToBGR8> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class WasmEdgeImageLoadPNGToRGB32F
    : public WasmEdgeImage<WasmEdgeImageLoadPNGToRGB32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};

class WasmEdgeImageLoadPNGToBGR32F
    : public WasmEdgeImage<WasmEdgeImageLoadPNGToBGR32F> {
public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};
class WasmedgeImageLoadJPGToLuma
    : public WasmEdgeImage<WasmedgeImageLoadJPGToLuma>{
  public:
  Expect<uint32_t> body(Runtime::Instance::MemoryInstance *MemInst,
                        uint32_t ImgBufPtr, uint32_t ImgBufLen,
                        uint32_t TargetImgW, uint32_t TargetImgH,
                        uint32_t DstBufPtr);
};
} // namespace Host
} // namespace WasmEdge