#!/bin/bash

CC -c cmathtest.cpp -o cmathtest.asm -S -fno-verbose-asm -fsource-asm -masm=intel -std=c++11 -I /global/homes/a/asarje/edison/hipgisaxs.git/include -I /usr/common/usg/boost/1.54/intel/include -I /include -I /opt/intel/composer_xe_2013.5.192/mkl/include -no-vec -DNOTIME -qopt-report -O1

CC -c mkltest.cpp -o mkltest.asm -S -fno-verbose-asm -fsource-asm -masm=intel -std=c++11 -I /global/homes/a/asarje/edison/hipgisaxs.git/include -I /usr/common/usg/boost/1.54/intel/include -I /include -I /opt/intel/composer_xe_2013.5.192/mkl/include -mkl -mavx -DNOTIME -qopt-report -O2


