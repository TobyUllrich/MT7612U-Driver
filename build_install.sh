#!/usr/bin/env bash

# clean any previous build
make clean

# build the driver
make -j4

# install the driver
sudo make install

# cleanup, no need binaries
make clean
