#!/usr/bin/env bash
CMAKE_BUILD_DIR="out"

rm -rf $CMAKE_BUILD_DIR
cmake . -B $CMAKE_BUILD_DIR 
cd $CMAKE_BUILD_DIR && make
