#!/bin/bash

make clean
make

rm info/exoAIStats.txt
touch info/exoAIStats.txt

#gnome-terminal -e 'watch -n 1 free -m'

#mpirun -np <number of processors> ./<executable>
echo "mpirun -np 4 ./ExoSAI"
mpirun -np 4 ./ExoSAI
#./ExoSAI
