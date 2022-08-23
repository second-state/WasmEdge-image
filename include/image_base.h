// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include "common/errcode.h"
#include "runtime/callingframe.h"
#include "runtime/hostfunc.h"

namespace WasmEdge {
namespace Host {

template <typename T> class WasmEdgeImage : public Runtime::HostFunction<T> {
public:
  WasmEdgeImage() : Runtime::HostFunction<T>(0) {}
};

} // namespace Host
} // namespace WasmEdge