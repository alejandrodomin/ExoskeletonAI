#!/bin/bash

make clean
make

echo "valgrind -v --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes ./ExoSAI"
valgrind -v --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes ./ExoSAI
