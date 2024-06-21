#!/bin/bash

sudo sysctl vm.mmap_rnd_bits=28 > /dev/null 2>&1
sudo sysctl vm.mmap_rnd_compat_bits=8 > /dev/null 2>&1

export LD_PRELOAD="/usr/lib/gcc/x86_64-linux-gnu/12/libasan.so ./dlclose.so"

./$(find ./bin -type f -print -quit)