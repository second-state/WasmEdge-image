// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include <sstream>
#include <string>
#include <vector>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/io/read_image.hpp>

#include "common/log.h"
#include "common/span.h"
#include "image_func.h"

namespace WasmEdge {
namespace Host {

namespace {
// Helper function to read jpeg buffer to gil::image
template <typename Image, typename FormatTag>
bool readBufToImg(const char *Buf, uint32_t Len, Image &Img,
                  FormatTag const &FTag) {
  std::stringstream ImgStream;
  ImgStream.write(Buf, Len);
  try {
    boost::gil::read_and_convert_image(ImgStream, Img, FTag);
  } catch (std::exception const &e) {
    spdlog::error(e.what());
    return false;
  }
  return true;
}

// Helper function to resize image. 8-bit depth only.
template <typename Image>
void resizeImg(const Image &Img, uint32_t W, uint32_t H, uint8_t *DstBuf) {
  uint32_t C = boost::gil::num_channels<typename Image::view_t>::value;
  typename Image::view_t ImgView = boost::gil::interleaved_view(
      W, H, reinterpret_cast<typename Image::value_type *>(DstBuf),
      W * C * sizeof(uint8_t));
  boost::gil::resize_view(boost::gil::const_view(Img), ImgView,
                          boost::gil::bilinear_sampler());
}

// Helper function to normalize image.
void normalizeImg(Span<const uint8_t> V, float *DstBuf) {
  for (uint32_t I = 0; I < V.size(); I++) {
    *(DstBuf + I) = V[I] / 255.0;
  }
}
} // namespace

Expect<uint32_t> WasmEdgeImageLoadJPGToRGB8::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  resizeImg(Img, TargetImgW, TargetImgH,
            MemInst->getPointer<uint8_t *>(DstBufPtr));
  return 0;
}

Expect<uint32_t> WasmEdgeImageLoadJPGToBGR8::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  resizeImg(Img, TargetImgW, TargetImgH,
            MemInst->getPointer<uint8_t *>(DstBufPtr));
  return 0;
}

Expect<uint32_t> WasmEdgeImageLoadJPGToRGB32F::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  std::vector<uint8_t> ImgData(3 * TargetImgW * TargetImgH);
  resizeImg(Img, TargetImgW, TargetImgH, ImgData.data());
  normalizeImg(ImgData, MemInst->getPointer<float *>(DstBufPtr));
  return 0;
}

Expect<uint32_t> WasmEdgeImageLoadJPGToBGR32F::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::jpeg_tag())) {
    return 1;
  }
  std::vector<uint8_t> ImgData(3 * TargetImgW * TargetImgH);
  resizeImg(Img, TargetImgW, TargetImgH, ImgData.data());
  normalizeImg(ImgData, MemInst->getPointer<float *>(DstBufPtr));
  return 0;
}

Expect<uint32_t> WasmEdgeImageLoadPNGToRGB8::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  resizeImg(Img, TargetImgW, TargetImgH,
            MemInst->getPointer<uint8_t *>(DstBufPtr));
  return 0;
}

Expect<uint32_t> WasmEdgeImageLoadPNGToBGR8::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  resizeImg(Img, TargetImgW, TargetImgH,
            MemInst->getPointer<uint8_t *>(DstBufPtr));
  return 0;
}

Expect<uint32_t> WasmEdgeImageLoadPNGToRGB32F::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::rgb8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  std::vector<uint8_t> ImgData(3 * TargetImgW * TargetImgH);
  resizeImg(Img, TargetImgW, TargetImgH, ImgData.data());
  normalizeImg(ImgData, MemInst->getPointer<float *>(DstBufPtr));
  return 0;
}

Expect<uint32_t> WasmEdgeImageLoadPNGToBGR32F::body(
    const Runtime::CallingFrame &Frame, uint32_t ImgBufPtr, uint32_t ImgBufLen,
    uint32_t TargetImgW, uint32_t TargetImgH, uint32_t DstBufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  boost::gil::bgr8_image_t Img;
  if (!readBufToImg(MemInst->getPointer<char *>(ImgBufPtr), ImgBufLen, Img,
                    boost::gil::png_tag())) {
    return 1;
  }
  std::vector<uint8_t> ImgData(3 * TargetImgW * TargetImgH);
  resizeImg(Img, TargetImgW, TargetImgH, ImgData.data());
  normalizeImg(ImgData, MemInst->getPointer<float *>(DstBufPtr));
  return 0;
}

} // namespace Host
} // namespace WasmEdge
