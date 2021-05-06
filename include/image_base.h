// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "common/errcode.h"
#include "runtime/hostfunc.h"

namespace WasmEdge {
namespace Host {

template <typename T> class WasmEdgeImage : public Runtime::HostFunction<T> {
public:
  WasmEdgeImage() : Runtime::HostFunction<T>(0) {}
};

} // namespace Host
} // namespace WasmEdge