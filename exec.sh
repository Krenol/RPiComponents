#!/bin/bash

mkdir build

export BUILD_TEST=ON

cmake -S . -B build/

cmake --build ./build || exit 1

./build/lib/rpicomponents_test_project