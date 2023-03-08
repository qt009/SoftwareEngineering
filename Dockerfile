FROM debian:latest

ARG zlib_repo="madler/zlib"
ARG zlib_tag="v1.2.11"
ARG zlib_prepare_cmd="./configure"
ARG zlib_build_cmd="make test"
ARG zlib_install_cmd="make install"

ARG cmake_repo="Kitware/CMake"
ARG cmake_tag="v3.14.3"
ARG cmake_prepare_cmd="./bootstrap --system-zlib --system-curl"
ARG cmake_build_cmd="make"
ARG cmake_install_cmd="make install"

ARG cppcheck_repo="danmar/cppcheck"
ARG cppcheck_tag="1.87"
ARG cppcheck_prepare_cmd="cmake -G \"Unix Makefiles\" -B build"
ARG cppcheck_build_cmd="cmake --build build"
ARG cppcheck_install_cmd="cmake --build build --target install"

ARG doxygen_repo="doxygen/doxygen"
ARG doxygen_tag="Release_1_8_15"
ARG doxygen_prepare_cmd="cmake -G \"Unix Makefiles\" -B build"
ARG doxygen_build_cmd="cmake --build build"
ARG doxygen_install_cmd="cmake --build build --target install"

ARG googletest_repo="google/googletest"
ARG googletest_tag="release-1.8.1"
ARG googletest_prepare_cmd="cmake -G \"Unix Makefiles\" -B build"
ARG googletest_build_cmd="cmake --build build"
ARG googletest_install_cmd="cmake --build build --target install"

ARG tinyxml2_repo="leethomason/tinyxml2"
ARG tinyxml2_tag="7.0.1"
ARG tinyxml2_prepare_cmd="cmake -G \"Unix Makefiles\" -B build"
ARG tinyxml2_build_cmd="cmake --build build"
ARG tinyxml2_install_cmd="cmake --build build --target install"

# Install the software where the version is not important
RUN apt-get update && apt-get -y install make gcc g++ graphviz git lcov cccc gitstats flex bison wget libcurl4-openssl-dev autoconf automake libtool groff-base perl

# Creating a directory to build the sources in
WORKDIR build


## zlib
# Download sources
RUN wget https://github.com/$zlib_repo/archive/$zlib_tag.tar.gz -O source.tar.gz && tar -xzf source.tar.gz --strip-components=1
# Prepare for build
RUN /bin/sh -c "$zlib_prepare_cmd"
# Build the sources
RUN /bin/sh -c "$zlib_build_cmd"
# Install binaries, libraries, and headers
RUN /bin/sh -c "$zlib_install_cmd"
# Clear the directory
RUN find . -mindepth 1 -delete
# Reload dynamic linker run-time bindings in case any shared library is not bound yet
RUN ldconfig


## CMake
# Download sources
RUN wget https://github.com/$cmake_repo/archive/$cmake_tag.tar.gz -O source.tar.gz && tar -xzf source.tar.gz --strip-components=1
# Prepare for build
RUN /bin/sh -c "$cmake_prepare_cmd"
# Build the sources
RUN /bin/sh -c "$cmake_build_cmd"
# Install binaries, libraries, and headers
RUN /bin/sh -c "$cmake_install_cmd"
# Clear the directory
RUN find . -mindepth 1 -delete
# Reload dynamic linker run-time bindings in case any shared library is not bound yet
RUN ldconfig


## CppCheck
# Download sources
RUN wget https://github.com/$cppcheck_repo/archive/$cppcheck_tag.tar.gz -O source.tar.gz && tar -xzf source.tar.gz --strip-components=1
# Prepare for build
RUN /bin/sh -c "$cppcheck_prepare_cmd"
# Build the sources
RUN /bin/sh -c "$cppcheck_build_cmd"
# Install binaries, libraries, and headers
RUN /bin/sh -c "$cppcheck_install_cmd"
# Clear the directory
RUN find . -mindepth 1 -delete
# Reload dynamic linker run-time bindings in case any shared library is not bound yet
RUN ldconfig


## Doxygen
# Download sources
RUN wget https://github.com/$doxygen_repo/archive/$doxygen_tag.tar.gz -O source.tar.gz && tar -xzf source.tar.gz --strip-components=1
# Prepare for build
RUN /bin/sh -c "$doxygen_prepare_cmd"
# Build the sources
RUN /bin/sh -c "$doxygen_build_cmd"
# Install binaries, libraries, and headers
RUN /bin/sh -c "$doxygen_install_cmd"
# Clear the directory
RUN find . -mindepth 1 -delete
# Reload dynamic linker run-time bindings in case any shared library is not bound yet
RUN ldconfig


## GoogleTest
# Download sources
RUN wget https://github.com/$googletest_repo/archive/$googletest_tag.tar.gz -O source.tar.gz && tar -xzf source.tar.gz --strip-components=1
# Prepare for build
RUN /bin/sh -c "$googletest_prepare_cmd"
# Build the sources
RUN /bin/sh -c "$googletest_build_cmd"
# Install binaries, libraries, and headers
RUN /bin/sh -c "$googletest_install_cmd"
# Clear the directory
RUN find . -mindepth 1 -delete
# Reload dynamic linker run-time bindings in case any shared library is not bound yet
RUN ldconfig


## TinyXML2
# Download sources
RUN wget https://github.com/$tinyxml2_repo/archive/$tinyxml2_tag.tar.gz -O source.tar.gz && tar -xzf source.tar.gz --strip-components=1
# Prepare for build
RUN /bin/sh -c "$tinyxml2_prepare_cmd"
# Build the sources
RUN /bin/sh -c "$tinyxml2_build_cmd"
# Install binaries, libraries, and headers
RUN /bin/sh -c "$tinyxml2_install_cmd"
# Clear the directory
RUN find . -mindepth 1 -delete
# Reload dynamic linker run-time bindings in case any shared library is not bound yet
RUN ldconfig


# Remove the build directory
WORKDIR ..
RUN rm -r build
