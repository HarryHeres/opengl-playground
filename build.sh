#!/usr/bin/env bash
rm -rf build
cmake . -B build
cd build && make
