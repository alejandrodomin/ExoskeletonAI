#!/bin/bash

make clean
make
valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./ExoSAI
