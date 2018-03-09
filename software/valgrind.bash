#!/bin/bash

make clean
make
valgrind -v --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes ./ExoSAI
