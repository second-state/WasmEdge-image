# Second State WebAssembly VM for Image Extension

The [Second State VM (SSVM)](https://github.com/second-state/ssvm) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [JPEG library](http://ijg.org/) and [PNG library](http://www.libpng.org/pub/png/libpng.html).

## Motivation

For this SSVM Image extension, we prefer to link the [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) statically into the SSVM Image static library. On the other hand, the C API shared library version of this SSVM Image extension requires the `libjpeg` and `libpng` shared library. Hence, we compile and release the pre-built static and shared library of [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) on the legacy operating system, and link them into our SSVM Image extension library for not only reducing the compilation time, but also saving the library installation.

## Requirements

The SSVM Image shared library `libssvm-image_c.so` is provided for the SSVM-Image extension of the SSVM shared library. When linking with this shared library, `libjpeg.so.8` and `libpng16.so.16` is required.

For `ubuntu 20.04`, the following commands can install these libraries:
```bash
$ sudo apt-get update
$ sudo apt-get install -y libjpeg-dev libpng-dev
```

Or you can download and install the pre-built shared libraries:

```bash
$ wget https://github.com/second-state/ssvm-image/releases/download/0.7.3/ssvm-image-deps-0.7.3-manylinux1_x86_64.tar.gz
$ tar -C /usr/local/lib -zxvf ssvm-image-deps-0.7.3-manylinux1_x86_64.tar.gz
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
$ docker pull secondstate/ssvm
```

### Or setup the environment manually

Please notice that SSVM-Image requires cmake>=3.11 and libboost>=1.68.

```bash
# Tools and libraries
$ sudo apt install -y \
	software-properties-common \
	cmake \
	libboost-all-dev

# And you will need to install llvm for ssvm-aot tools
$ sudo apt install -y \
	llvm-dev \
	liblld-10-dev

# SSVM supports both clang++ and g++ compilers
# You can choose one of them for building this project
$ sudo apt install -y gcc g++
$ sudo apt install -y clang
```

## Get SSVM-Image Source Code

```bash
$ git clone --recursive git@github.com:second-state/ssvm-image.git
$ cd ssvm-image
$ git checkout 0.7.3
```

## Build SSVM-Image

SSVM-Image depends on SSVM-Core, you have to prepare SSVM-Core before you build SSVM-Image.
We provides two options for setting up the SSVM-Core:

### Create and Enter the Build Folder

```bash
# After pulling our ssvm docker image
$ docker run -it --rm \
    -v <path/to/your/ssvm-tensorflow/source/folder>:/root/ssvm-image \
    secondstate/ssvm:latest
(docker)$ cd /root/ssvm-image
(docker)$ mkdir -p build && cd build
```

### Option 1. Use built-in CMakeLists to get SSVM-Core (Recommended)

```bash
(docker)$ cmake -DCMAKE_BUILD_TYPE=Release .. && make
```

### Option 2. Use specific version of SSVM-Core by giving SSVM_CORE_PATH

```bash
(docker)$ cmake -DSSVM_CORE_PATH=<path/to/ssvm/source> -DCMAKE_BUILD_TYPE=Release .. && make
```

The executable `build/tools/ssvmc-tensorflow` is the AOT compiler for WASM files.

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
$ docker pull secondstate/ssvm:manylinux1_x86_64
$ docker run -it --rm -v $(pwd):/root/$(basename $(pwd)) secondstate/ssvm:manylinux1_x86_64
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
