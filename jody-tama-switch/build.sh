#!/bin/bash
echo "Building Jody-Tama for Nintendo Switch..."
mkdir -p build
cd build
cmake ..
make
