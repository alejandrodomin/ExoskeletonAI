#!/bin/bash

make clean
make
rm exoAIStats.txt
touch exoAIStats.txt
gnome-terminal -e 'tail -f exoAIStats.txt'
gnome-terminal -e 'tail -f info_proc.txt'
gnome-terminal -e 'watch -n 1 free -m'

#mpirun -np <number of processors> ./<executable>
mpirun -np 4 ./ExoSAI
#./ExoSAI
