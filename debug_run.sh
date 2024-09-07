#!/bin/bash

# export LD_PRELOAD="/usr/lib/gcc/x86_64-linux-gnu/12/libasan.so ./dlclose.so"

./$(find ./bin -type f -print -quit)