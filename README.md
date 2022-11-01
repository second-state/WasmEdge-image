# WasmEdge for Image Extension

The [WasmEdge](https://github.com/WasmEdge/WasmEdge) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [JPEG library](http://ijg.org/), [libjpeg-turbo library](https://libjpeg-turbo.org/), and [PNG library](http://www.libpng.org/pub/png/libpng.html).

## Motivation

For this WasmEdge Image extension, we prefer to link the [libjpeg](http://ijg.org/), [libjpeg-turbo](https://libjpeg-turbo.org/), and [libpng](http://www.libpng.org/pub/png/libpng.html) statically into the both WasmEdge Image static and shared library. Hence, we compile and release the pre-built static library of [libjpeg](http://ijg.org/), [libjpeg-turbo](https://libjpeg-turbo.org/), and [libpng](http://www.libpng.org/pub/png/libpng.html) on the legacy operating systems or for the Android platforms, and link them into our WasmEdge Image extension library for not only reducing the compilation time, but also saving the library installation.

## License

This project is under the License as the same as the [libjpeg](http://ijg.org/), [libjpeg-turbo](https://libjpeg-turbo.org/), and [libpng](http://www.libpng.org/pub/png/libpng.html) projects.

### Credits

- [libjpeg](http://ijg.org/)
- [libjpeg-turbo](https://libjpeg-turbo.org/)
- [libpng](http://www.libpng.org/pub/png/libpng.html)

## Getting Started

### Prepare the environment

#### Use our docker image (Recommanded)

Our docker image is based on `ubuntu 20.04`.

```bash
docker pull wasmedge/wasmedge
```

#### Or setup the environment manually

Please notice that WasmEdge-Image requires cmake>=3.11 and libboost>=1.68.

```bash
# Tools and libraries
sudo apt install -y \
    software-properties-common \
    cmake \
    libboost-all-dev

# WasmEdge supports both clang++ and g++ compilers
# You can choose one of them for building this project
sudo apt install -y gcc g++
sudo apt install -y clang
```

### Get WasmEdge-Image Source Code

```bash
git clone https://github.com/second-state/WasmEdge-image.git
cd WasmEdge-image
git checkout 0.11.2-rc.3
```

### Build WasmEdge-Image

WasmEdge-Image depends on WasmEdge-Core, you have to prepare WasmEdge-Core before you build WasmEdge-Image.
We provides two options for setting up the WasmEdge-Core:

#### Create and Enter the Build Folder

```bash
# After pulling our WasmEdge docker image
docker run -it --rm \
    -v <path/to/your/WasmEdge-image/source/folder>:/root/WasmEdge-image \
    wasmedge/wasmedge:latest
# In docker
cd /root/WasmEdge-image
mkdir -p build && cd build
```

#### Option 1. Use built-in CMakeLists to get WasmEdge-Core (Recommended)

```bash
# In docker
cmake -DCMAKE_BUILD_TYPE=Release .. && make
```

#### Option 2. Use specific version of WasmEdge-Core by giving WASMEDGE_CORE_PATH

```bash
# In docker
cmake -DWASMEDGE_CORE_PATH=<path/to/WasmEdge/source> -DCMAKE_BUILD_TYPE=Release .. && make
```

The shared library `build/lib/libwasmedge-image_c.so` is the C API to create `wasmedge-image` import object.
The header `build/include/wasmedge/wasmedge-image.h` is the header of the shared library.
The static library `build/lib/libwasmedgeHostModuleWasmEdgeImage.a` is for executables linking in CMake.

## How to build `libjpeg` and `libpng` on the legacy operating system - CentOS 5.11 x86_64

### Download the libjpeg and libpng source on CentOS 7.9 x86_64

```bash
mkdir workspace && cd workspace
curl -sLO https://downloads.sourceforge.net/libpng/libpng-1.6.37.tar.xz
tar Jxvf libpng-1.6.37.tar.xz
curl -sLO http://ijg.org/files/jpegsrc.v8c.tar.gz
tar -zxvf jpegsrc.v8c.tar.gz
```

### Pull the manylinux2014_x86_64 docker image and run

```bash
docker pull wasmedge/wasmedge:manylinux2014_x86_64
docker run -it --rm -v $(pwd):/root/$(basename $(pwd)) wasmedge/wasmedge:manylinux2014_x86_64
```

### Build the libjpeg and the libpng for manylinux2014_x86_64

```bash
# In docker
cd /root/workspace/jpeg-8c
CFLAGS=-fPIC ./configure --enable-shared=off && make
# The JPEG static library will be at `.libs/libjpeg.a`.
cd /root/workspace/libpng-1.6.37
CFLAGS=-fPIC ./configure --enable-shared=off && make
# The PNG static library will be at `.libs/libpng16.a`.
```

## How to build `libjpeg` and `libpng` on the legacy operating system - CentOS 7.9 aarch64

### Download the libjpeg and libpng source on CentOS 7.9 aarch64

```bash
mkdir workspace && cd workspace
curl -sLO https://downloads.sourceforge.net/libpng/libpng-1.6.37.tar.xz
tar Jxvf libpng-1.6.37.tar.xz
curl -sLO http://ijg.org/files/jpegsrc.v8c.tar.gz
tar -zxvf jpegsrc.v8c.tar.gz
```

### Pull the manylinux2014_aarch64 docker image and run

```bash
docker pull wasmedge/wasmedge:manylinux2014_aarch64
docker run -it --rm -v $(pwd):/root/$(basename $(pwd)) wasmedge/wasmedge:manylinux2014_aarch64
```

### Build the libjpeg and the libpng for manylinux2014_aarch64

```bash
# In docker
cd /root/workspace/jpeg-8c
CFLAGS=-fPIC ./configure --enable-shared=off --build=aarch64-unknown-linux-gnu && make
# The JPEG static library will be at `.libs/libjpeg.a`.
cd /root/workspace/libpng-1.6.37
CFLAGS=-fPIC ./configure --enable-shared=off --build=aarch64-unknown-linux-gnu && make
# The PNG static library will be at `.libs/libpng16.a`.
```

## How to use Android NDK to cross-compile `libjpeg-turbo` and `libpng` for Android aarch64

### Download the libjpeg-turbo and libpng source on Ubuntu 20.04

```bash
mkdir workspace && cd workspace
curl -sLO https://downloads.sourceforge.net/libpng/libpng-1.6.37.tar.xz
tar Jxvf libpng-1.6.37.tar.xz
curl -sL https://github.com/libjpeg-turbo/libjpeg-turbo/archive/refs/tags/2.1.2.tar.gz -o libjpeg-turbo-2.1.2.tar.gz
tar -zxvf libjpeg-turbo-2.1.2.tar.gz
```

### Download Android NDK and set the environment

Download the NDK from [android website](https://developer.android.com/ndk/downloads).

```bash
curl -sLO https://dl.google.com/android/repository/android-ndk-r23b-linux.zip
unzip -q android-ndk-r23b-linux.zip
```

### Pull the WasmEdge docker image and run

```bash
docker pull wasmedge/wasmedge:latest
docker run -it --rm -v $(pwd):/root/$(basename $(pwd)) wasmedge/wasmedge:latest
```

### Build the libjpeg and the libpng for android

```bash
# In docker
export ANDROID_NDK_HOME=/root/workspace/android-ndk-r23b
cd /root/workspace/libjpeg-turbo-2.1.2
cmake -GNinja -DANDROID_ABI=arm64-v8a -DANDROID_ARM_MODE=arm -DANDROID_PLATFORM=android-23 -DANDROID_TOOLCHAIN=clang -DCMAKE_ASM_FLAGS="--target=aarch64-linux-android23" -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DENABLE_SHARED=FALSE -DWITH_JPEG8=1 -Bbuild .
cmake --build build
# The JPEG static library will be at `./build/libjpeg.a`.
cd /root/workspace/libpng-1.6.37
cmake -GNinja -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-23 -DANDROID_NDK=$ANDROID_NDK_HOME -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DPNG_SHARED=OFF -Bbuild .
cmake --build build
# The PNG static library will be at `./build/libpng16.a`.
```

## Minimum requirements of our pre-built static libraries

| Pre-built static library         | Architecture | Supported operating systems         |
| -------------------------------- | ------------ | ----------------------------------- |
| libjpeg_android_aarch64.a        | arm64-v8a    | Android 23 or later                 |
| libpng16_android_aarch64.a       | arm64-v8a    | Android 23 or later                 |
| libjpeg_manylinux2014_aarch64.a  | aarch64      | manylinux2014 or later (GLIBC 2.17) |
| libpng16_manylinux2014_aarch64.a | aarch64      | manylinux2014 or later (GLIBC 2.17) |
| libjpeg_manylinux2014_x86_64.a   | x86_64       | manylinux2014 or later (GLIBC 2.17) |
| libpng16_manylinux2014_x86_64.a  | x86_64       | manylinux2014 or later (GLIBC 2.17) |
| libjpeg_darwin_x86_64.a          | x86_64       | MacOS 10.15 or later                |
| libpng16_darwin_x86_64.a         | x86_64       | MacOS 10.15 or later                |
