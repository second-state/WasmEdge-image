### 0.10.1-alpha.1 (2022-06-22)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.10.1-alpha.1](https://github.com/WasmEdge/WasmEdge/releases/tag/0.10.1-alpha.1) for more details.

Features:

* Update the `WasmEdge` dependency to `0.10.1-alpha.1`.

### 0.10.0 (2022-05-26)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.10.0](https://github.com/WasmEdge/WasmEdge/releases/tag/0.10.0) for more details.

Breaking changes:

* Renamed C API `WasmEdge_Image_ImportObjectCreate` to `WasmEdge_Image_ModuleInstanceCreate`.

Features:

* Update the `WasmEdge` dependency to `0.10.0`.
* Added the Darwin x86_64 support.

### 0.9.1 (2022-02-10)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.9.1](https://github.com/WasmEdge/WasmEdge/releases/tag/0.9.1) for more details.

Features:

* Added the copyright text.
* Update the `WasmEdge` dependency to `0.9.1`.
* Added the Linux aarch64 support.
* Added the Android aarch64 support.

### 0.9.0 (2021-12-09)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.9.0](https://github.com/WasmEdge/WasmEdge/releases/tag/0.9.0) for more details.

Breaking changes:

* Moved the C-API headers `wasmedge-image.h` and `wasmedge-image.h` into the `wasmedge` folder.

Features:

* Update the `WasmEdge` dependency to `0.9.0`.

### 0.8.2 (2021-09-03)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.8.2](https://github.com/WasmEdge/WasmEdge/releases/tag/0.8.2) for more details.

Features:

* Update the `WasmEdge` dependency to `0.8.2`.
* Modified the CMake option `BUILD_SHARED_LIB` to `WASMEDGE_IMAGE_BUILD_SHARED_LIB` for enabling compilation of the shared library (`ON` by default).

### 0.8.1 (2021-06-22)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.8.1](https://github.com/WasmEdge/WasmEdge/releases/tag/0.8.1) for more details.

Features:

* Update the `WasmEdge` dependency to `0.8.1`.

### 0.8.0 (2021-05-14)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.8.0](https://github.com/WasmEdge/WasmEdge/releases/tag/0.8.0) for more details.

Features:

* Renamed this project to `WasmEdge-Image` and updated the `WasmEdge` dependency.
* Added pre-built `libpng` and `libjpeg` shared libraries.
* Added `wasmedge-image` C API shared library.
* Added CMake option `BUILD_SHARED_LIB` to enable compiling the shared library (`ON` by default).
* Added release CI.

### 0.7.3 (2021-02-03)

This is the host function extension for [SSVM](https://github.com/second-state/SSVM).
Please refer to the [SSVM 0.7.3](https://github.com/second-state/SSVM/releases/tag/0.7.3) for more details.

Features:

* Image processing host function extensions of WASM
  * Support reading `JPEG` and `PNG` from a buffer.
  * Support the `rgb8` and `rgb32f` normalized formats.
  * Support image resizing.
