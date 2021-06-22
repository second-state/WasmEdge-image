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

### 0.8.0-rc2 (2021-05-07)

This is the host function extension for [WasmEdge](https://github.com/WasmEdge/WasmEdge).
Please refer to the [WasmEdge 0.8.0](https://github.com/WasmEdge/WasmEdge/releases/tag/0.8.0) for more details.

Features:

* Renamed this project to `WasmEdge-Image` and updated the `WasmEdge` dependency.
* Added pre-built `libpng` and `libjpeg` shared libraries.
* Added `wasmedge-image` C API shared library.
* Added release CI.

### 0.8.0-rc1 (2021-04-30)

This is the host function extension for [SSVM](https://github.com/second-state/SSVM).
Please refer to the [SSVM 0.7.3](https://github.com/second-state/SSVM/releases/tag/0.7.3) for more details.

Features:

* Add pre-built `libpng` and `libjpeg` shared libraries.
* Add ssvm-image C API shared library.
* Add release CI.

### 0.7.3 (2021-02-03)

This is the host function extension for [SSVM](https://github.com/second-state/SSVM).
Please refer to the [SSVM 0.7.3](https://github.com/second-state/SSVM/releases/tag/0.7.3) for more details.

Features:

* Image processing host function extensions of WASM
  * Support reading `JPEG` and `PNG` from a buffer.
  * Support the `rgb8` and `rgb32f` normalized formats.
  * Support image resizing.
