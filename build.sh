#!/bin/sh

rm -rf build/ && rm -rf deploy/
mkdir build/ && mkdir deploy/
cd build/
cmake ..
cmake --build .
cd -
cp build/work_init_c_run deploy/
cp init.sh deploy/
cp work_init_client.sh deploy/
cd deploy/
./work_init_c_run
