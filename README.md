# Artemis

## _3rd-party library for Higiia client_

This repository contains a C++ wrapper library for managing PNG, BMP, PNG, KRL and DICOM images. It was originally designed fo wrapping OpenCV2.0 and DCMTK, but currently it relies on [Qt SDK](https://www.qt.io/download) and [dicomlib](https://github.com/marcosivni/dicomlib) for performing low-level file-based operations.


Artemis code can be compiled under Qt for a broad set of platforms, including WebAssembly. The repository version was succesfully compiled with Emscripten coupled to Qt 5.15.1 with [em++](https://emscripten.org/docs/getting_started/downloads.html) compiler v2.0.22.

## 3rd-party dependencies

- Self-contained header-only files from C++ [Boost library](https://www.boost.org/users/download/)
- [Dicomlib](https://github.com/marcosivni/dicomlib)

## Installation

1. Install Boost headers.
2. Download and install [dicomlib]((https://github.com/marcosivni/dicomlib)).
3. Adjust the include paths of the `artemis.pro.example` file to point to the Boost and dicomlib folders. 
4. Rename `artemis.pro.example` to `artemis.pro`. 
5. Use build.sh to create the static lib files. Notice, you can configure the building type in the `build.sh` file itself by selecting the qmake binary of your QT setup (e.g., wasm\_32 (default) or gcc\_64).

```sh
#!/bin/sh
/Qt/5.15.1/wasm_32/bin/qmake   #for Web-Assembly building
#/Qt/5.15.1/gcc_64/bin/qmake   #for desktop-binary building
make
```

Then, run the following command.

```sh
cd artemis
./build.sh && make clean
```

It will create the static library you can link to your [Higiia project](https://github.com/marcosivni/higiia). Best of luck!

