#!/bin/sh

echo "Initializing compilation..."
cd build && cmake .. && make
echo "Compilation finished."
