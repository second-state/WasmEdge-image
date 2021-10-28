// SPDX-License-Identifier: Apache-2.0
//===-- WasmEdge-image/wasmedge-image.h - WasmEdge Image C API ------------===//
//
// Part of the WasmEdge Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the function declarations of WasmEdge Image C API.
///
//===----------------------------------------------------------------------===//

#ifndef __WASMEDGE_IMAGE_C_API_H__
#define __WASMEDGE_IMAGE_C_API_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// Need to install the WasmEdge C library first.
#include <wasmedge/wasmedge.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Creation of the WasmEdge_ImportObjectContext for the wasmedge_image host
/// functions.
///
/// The caller owns the object and should call `WasmEdge_ImportObjectDelete` to
/// free it.
///
/// \returns pointer to context, NULL if failed.
WASMEDGE_CAPI_EXPORT extern WasmEdge_ImportObjectContext *
WasmEdge_Image_ImportObjectCreate();

#ifdef __cplusplus
} /// extern "C"
#endif

#endif /// __WASMEDGE_IMAGE_C_API_H__