#!/bin/bash

# store the pwd in a variable to return where the script was run from
pwd=$(pwd)

# compile the monkey implementation
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

# return the pwd where we started
cd $pwd

