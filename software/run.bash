#!/bin/bash

make clean
make
gnome-terminal -e 'tail -f exoAIStats.txt'
gnome-terminal -e 'watch -n 5 free -m'
./ExoSAI
