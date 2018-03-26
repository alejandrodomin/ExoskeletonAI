#!/bin/bash

echo "This might take a while to execute, however it is necessary for everything to work."
read -p "This setup should only be run once, would you like to run it? (y/n)" CONT

if [ "$CONT" = "n" ]; then
	echo "Unecessary actions aborted."
elif [ "$CONT" = "y" ]; then
	echo "Setting Path Variables."
	if ! echo "$PATH" | /bin/grep -Eq "ExoskeletonAI/software/" ; then
		echo "export PATH=$PATH:$PWD/software/include" >> ~/.bashrc
	fi

	sudo apt update

	read -p "Would you like to install VSCode: (y/n)" ANSW
	if [ "$ANSW" = "y" ]; then
		sudo apt install snapd-xdg-open
		sudo snap install vscode --classic
	else
		echo "Aborting instalation of VSCode."
	fi

	echo "Installing Boost C++ Library"
	sudo apt install libboost-all-dev

	echo "Installing MPI."
	sudo apt install openmpi-bin openmpi-common openssh-client openssh-server libopenmpi1.10 libopenmpi-dev

	echo "Installing Doxygen."
	sudo apt install doxygen

	echo "Installing Google Test support."
	sudo apt install libgtest-dev
	sudo apt install cmake
	cd /usr/src/gtest
	sudo cmake CMakeLists.txt
	sudo make
	sudo cp *.a /usr/lib

	sudo reboot
else
	echo "Command not recognized, aborting setup."
fi
