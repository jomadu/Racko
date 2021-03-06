#!/bin/bash

if [[ "$1" == "-d" || "$1" == "--debug" ]]; then
    echo "Building for debug"
    cd build/
    cmake -DCMAKE_BUILD_TYPE=Debug ../..
    cmake --build .
else
    echo "Building for release"
    cd build/
    cmake -DCMAKE_BUILD_TYPE=Release ../..
    cmake --build .
fi
