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

	sudo apt-get update

	read -p "Would you like to install VSCode: (y/n)" ANSW
	if [ "$ANSW" = "y" ]; then
		sudo apt-get install snapd-xdg-open
		sudo snap install vscode --classic
	else
		echo "Aborting instalation of VSCode."
	fi

	echo "Installing MPI."
	sudo apt-get install openmpi-bin openmpi-common openssh-client openssh-server libopenmpi1.10 libopenmpi-dev

	echo "Installing Doxygen."
	sudo apt-get install doxygen

	echo "Installing Google Test support."
	sudo apt-get install libgtest-dev
	sudo apt-get install cmake
	cd /usr/src/gtest
	sudo cmake CMakeLists.txt
	sudo make
	sudo cp *.a /usr/lib

#	sudo reboot
else
	echo "Command not recognized, aborting setup."
fi
