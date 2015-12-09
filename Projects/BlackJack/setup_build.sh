#!/bin/bash
mkdir build
cp -r res/ build/
cd build
cmake ..
make
