#!/bin/bash

echo "This might take a while to execute, however it is necessary for everything to work."
read -p "This setup should only be run once, would you like to run it? (y/n)" CONT

if [ "$CONT" = "n" ]; then
	echo "Unecessary actions aborted."
else
	echo "Setting Path Variables."
	if ! echo "$PATH" | /bin/grep -Eq "ExoskeletonAI/software/" ; then
		echo "export PATH=$PATH:$PWD/software/include" >> ~/.bashrc
	fi
	
	sudo apt-get update

	echo "Installing Doxygen."
	sudo apt-get install doxygen

	echo "Installing Google Test support."
	sudo apt-get install libgtest-dev
	sudo apt-get install cmake
	cd /usr/src/gtest
	sudo cmake CMakeLists.txt
	sudo make
	sudo cp *.a /usr/lib

	sudo reboot
fi
