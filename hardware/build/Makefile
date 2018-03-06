CC = gcc
.PHONY: all
all: gyro

gyro: gyroscope.cpp
	$(CC) -Wall -O2 gyroscope.cpp -o gyro -llsm9ds1

clean:
	rm -f gyro
