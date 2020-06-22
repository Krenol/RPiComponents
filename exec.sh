#!/bin/bash

mkdir build

export BUILD_TEST=ON

cmake -S rpicomponents/ -B build/

cmake --build ./build || exit 1



./rpicomponents/build/rpicomponents_test_project