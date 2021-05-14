# WasmEdge for Image Extension

The [WasmEdge](https://github.com/WasmEdge/WasmEdge) (formerly `SSVM`) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [JPEG library](http://ijg.org/) and [PNG library](http://www.libpng.org/pub/png/libpng.html).

## Motivation

For this WasmEdge Image extension, we prefer to link the [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) statically into the WasmEdge Image static library. On the other hand, the C API shared library version of this WasmEdge Image extension requires the `libjpeg` and `libpng` shared library. Hence, we compile and release the pre-built static and shared library of [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) on the legacy operating system, and link them into our WasmEdge Image extension library for not only reducing the compilation time, but also saving the library installation.

## Requirements

The WasmEdge Image shared library `libwasmedge-image_c.so` is provided for the WasmEdge-Image extension of the WasmEdge shared library. When linking with this shared library, `libjpeg.so.8` and `libpng16.so.16` is required.

For `ubuntu 20.04`, the following commands can install these libraries:
```bash
$ sudo apt-get update
$ sudo apt-get install -y libjpeg-dev libpng-dev
```

Or you can download and install the pre-built shared libraries:

```bash
$ wget https://github.com/second-state/wasmedge-image/releases/download/0.8.0/WasmEdge-image-deps-0.8.0-manylinux1_x86_64.tar.gz
$ tar -C /usr/local/lib -zxvf WasmEdge-image-deps-0.8.0-manylinux1_x86_64.tar.gz
$ ln -s /usr/local/lib/libjpeg.so.8.3.0 /usr/local/lib/libjpeg.so
$ ln -s /usr/local/lib/libpng16.so.16.37.0 /usr/local/lib/libpng.so
$ ldconfig
```

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
$ git checkout 0.8.0
```

## Build WasmEdge-Image

WasmEdge-Image depends on WasmEdge-Core, you have to prepare WasmEdge-Core before you build WasmEdge-Image.
We provides two options for setting up the WasmEdge-Core:

### Create and Enter the Build Folder

```bash
# After pulling our WasmEdge docker image
$ docker run -it --rm \
    -v <path/to/your/WasmEdge-tensorflow/source/folder>:/root/WasmEdge-tensorflow \
    wasmedge/wasmedge:latest
(docker)$ cd /root/WasmEdge-tensorflow
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
The header `build/include/wasmedge-image.h` is the header of the shared library.
The static library `build/lib/libwasmedgeHostModuleWasmEdgeImage.a` is for executables linking in CMake.

# How to build `libjpeg` and `libpng` on the legacy operating system - CentOS 5.11

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
(docker) $ ./configure && make
# The JPEG shared library will be at `.libs/libjpeg.so.8.3.0`, and the static library will be at `.libs/libjpeg.a`.
(docker) $ cd /root/workspace/libpng-1.6.37
(docker) $ ./configure && make
# The PNG shared library will be at `.libs/libpng16.so.16.37.0`, and the static library will be at `.libs/libpng16.a`.
```

# Minimum requirements of our pre-built shared libraries

| Pre-built shared library          | GLIBC          | GLIBCXX       | CXXABI          |
| --------------------------        | -------------- | ------------- | --------------- |
| libjpeg.so.8                      | 2.14           | -             | -               |
| libpng16.so.16                    | 2.14           | -             | -               |
