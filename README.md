# WasmEdge for Image Extension

The [WasmEdge](https://github.com/WasmEdge/WasmEdge) (formerly `SSVM`) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [JPEG library](http://ijg.org/) and [PNG library](http://www.libpng.org/pub/png/libpng.html).

## Motivation

For this WasmEdge Image extension, we prefer to link the [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) statically into the both WasmEdge Image static and shared library. Hence, we compile and release the pre-built static and shared library of [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) on the legacy operating system, and link them into our WasmEdge Image extension library for not only reducing the compilation time, but also saving the library installation.

## License

This project is under the License as the same as the [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) projects.

### Credits

- [libjpeg](http://ijg.org/)
- [libpng](http://www.libpng.org/pub/png/libpng.html)

# Getting Started

## Prepare the environment

### Use our docker image (Recommanded)

Our docker image is based on `ubuntu 20.04`.

```bash
$ docker pull wasmedge/wasmedge
```

### Or setup the environment manually

Please notice that WasmEdge-Image requires cmake>=3.11 and libboost>=1.68.

```bash
# Tools and libraries
$ sudo apt install -y \
	software-properties-common \
	cmake \
	libboost-all-dev

# WasmEdge supports both clang++ and g++ compilers
# You can choose one of them for building this project
$ sudo apt install -y gcc g++
$ sudo apt install -y clang
```

## Get WasmEdge-Image Source Code

```bash
$ git clone https://github.com/second-state/WasmEdge-image.git
$ cd WasmEdge-image
$ git checkout 0.9.1-beta.2
```

## Build WasmEdge-Image

WasmEdge-Image depends on WasmEdge-Core, you have to prepare WasmEdge-Core before you build WasmEdge-Image.
We provides two options for setting up the WasmEdge-Core:

### Create and Enter the Build Folder

```bash
# After pulling our WasmEdge docker image
$ docker run -it --rm \
    -v <path/to/your/WasmEdge-image/source/folder>:/root/WasmEdge-image \
    wasmedge/wasmedge:latest
(docker)$ cd /root/WasmEdge-image
(docker)$ mkdir -p build && cd build
```

### Option 1. Use built-in CMakeLists to get WasmEdge-Core (Recommended)

```bash
(docker)$ cmake -DCMAKE_BUILD_TYPE=Release .. && make
```

### Option 2. Use specific version of WasmEdge-Core by giving WASMEDGE_CORE_PATH

```bash
(docker)$ cmake -DWASMEDGE_CORE_PATH=<path/to/WasmEdge/source> -DCMAKE_BUILD_TYPE=Release .. && make
```

The shared library `build/lib/libwasmedge-image_c.so` is the C API to create `wasmedge-image` import object.
The header `build/include/wasmedge/wasmedge-image.h` is the header of the shared library.
The static library `build/lib/libwasmedgeHostModuleWasmEdgeImage.a` is for executables linking in CMake.

# How to build `libjpeg` and `libpng` on the legacy operating system - CentOS 5.11 x86_64

## Download the libjpeg and libpng source

```bash
$ mkdir workspace && cd workspace
$ wget https://downloads.sourceforge.net/libpng/libpng-1.6.37.tar.xz
$ tar Jxvf libpng-1.6.37.tar.xz
$ wget http://ijg.org/files/jpegsrc.v8c.tar.gz
$ tar -zxvf jpegsrc.v8c.tar.gz
```

## Pull the manylinux1 docker image and run

```bash
$ docker pull wasmedge/wasmedge:manylinux1_x86_64
$ docker run -it --rm -v $(pwd):/root/$(basename $(pwd)) wasmedge/wasmedge:manylinux1_x86_64
```

## Build the libjpeg and the libpng

```bash
(docker) $ cd /root/workspace/jpeg-8c
(docker) $ CFLAGS=-fPIC ./configure --enable-shared=off && make
# The JPEG static library will be at `.libs/libjpeg.a`.
(docker) $ cd /root/workspace/libpng-1.6.37
(docker) $ CFLAGS=-fPIC ./configure --enable-shared=off && make
# The PNG static library will be at `.libs/libpng16.a`.
```

# How to build `libjpeg` and `libpng` on the legacy operating system - CentOS 7.9 aarch64

## Download the libjpeg and libpng source

```bash
$ mkdir workspace && cd workspace
$ wget https://downloads.sourceforge.net/libpng/libpng-1.6.37.tar.xz
$ tar Jxvf libpng-1.6.37.tar.xz
$ wget http://ijg.org/files/jpegsrc.v8c.tar.gz
$ tar -zxvf jpegsrc.v8c.tar.gz
```

## Pull the manylinux2014_aarch64 docker image and run

```bash
$ docker pull wasmedge/wasmedge:manylinux2014_aarch64
$ docker run -it --rm -v $(pwd):/root/$(basename $(pwd)) wasmedge/wasmedge:manylinux2014_aarch64
```

## Build the libjpeg and the libpng

```bash
(docker) $ cd /root/workspace/jpeg-8c
(docker) $ CFLAGS=-fPIC ./configure --enable-shared=off --build=aarch64-unknown-linux-gnu && make
# The JPEG static library will be at `.libs/libjpeg.a`.
(docker) $ cd /root/workspace/libpng-1.6.37
(docker) $ CFLAGS=-fPIC ./configure --enable-shared=off --build=aarch64-unknown-linux-gnu && make
# The PNG static library will be at `.libs/libpng16.a`.
```

# How to use Android NDK to cross-compile `libjpeg` and `libpng` for Android aarch64 

## Download the libjpeg and libpng source

```bash
$ mkdir workspace && cd workspace
$ wget https://downloads.sourceforge.net/libpng/libpng-1.6.37.tar.xz
$ tar Jxvf libpng-1.6.37.tar.xz
$ git clone https://github.com/stohrendorf/libjpeg-cmake
```

## Download Android NDK and set the environment
Download the NDK from [android website](https://developer.android.com/ndk/downloads).
```bash
$ export ANDROID_NDK_HOME=/path/to/ndk
```

## Build the libjpeg and the libpng

```bash
$ cd libjpeg-cmake && mkdir build && cd build
$ cmake .. -GNinja -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-23 -DANDROID_NDK=$ANDROID_NDK_HOME -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake
$ ninja
# The JPEG static library will be at `libjpeg-cmake/build/liblibjpeg.a`.

$ cd libpng-1.6.37 && mkdir build && cd build
$ cmake .. -GNinja -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-23 -DANDROID_NDK=$ANDROID_NDK_HOME -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DPNG_SHARED=OFF
$ ninja
# The PNG static library will be at `libpng-1.6.37/build/libpng16.a`.
```
