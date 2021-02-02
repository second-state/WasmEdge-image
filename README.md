# Second State WebAssembly VM for Image Extension

The [Second State VM (SSVM)](https://github.com/second-state/ssvm) is a high performance WebAssembly runtime optimized for server side applications. This project provides support for accessing with [JPEG library](http://ijg.org/) and [PNG library](http://www.libpng.org/pub/png/libpng.html).

## Motivation

For this SSVM Image extension, we prefer to link the [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) statically. Hence, we compile and release the pre-built static library of [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) on the legacy operating system, and link them into our SSVM Image extension library for not only reducing the compilation time, but also saving the library installation.

## License

This project is under the License as the same as the [libjpeg](http://ijg.org/) and [libpng](http://www.libpng.org/pub/png/libpng.html) projects.

### Credits

- [libjpeg](http://ijg.org/)
- [libpng](http://www.libpng.org/pub/png/libpng.html)

## How to build on the legacy operating system - CentOS 5.11

### Download the libjpeg and libpng source

```bash
$ mkdir workspace && cd workspace
$ wget https://downloads.sourceforge.net/libpng/libpng-1.6.37.tar.xz
$ tar Jxvf libpng-1.6.37.tar.xz
$ wget http://ijg.org/files/jpegsrc.v8c.tar.gz
$ tar -zxvf jpegsrc.v8c.tar.gz
```

### Pull the manylinux1 docker image and run

```bash
$ docker pull secondstate/ssvm:manylinux1_x86_64
$ docker run -it --rm -v $(pwd):/root/$(basename $(pwd)) secondstate/ssvm:manylinux1_x86_64
```

### Install gcc

```bash
(docker) $ yum update
(docker) $ yum install -y make gcc gcc-c++
```

### Build the libjpeg and the libpng

```bash
(docker) $ cd /root/workspace/jpeg-8c
(docker) $ ./configure && make
# The JPEG shared library will be at `.libs/libjpeg.so.8.3.0`, and the static library will be at `.libs/libjpeg.a`.
(docker) $ cd /root/workspace/libpng-1.6.37
(docker) $ ./configure && make
# The PNG shared library will be at `.libs/libpng16.so.16.37.0`, and the static library will be at `.libs/libpng16.a`.
```
