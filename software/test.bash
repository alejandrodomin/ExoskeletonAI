#!/bin/bash

make clean
make
valgrind -v ./ExoSAI
