CC = mpic++
SRC := src
OBJ := build
INC := include

DEBUG = -g
LFLAGS = -llsm9ds1 -pthread -L/usr//lib -L/usr/lib/arm-linux-gnueabihf/openmpi/lib -lmpi_cxx -lmpi -L/usr/local/lib -lwiringPi
CFLAGS = -Wfatal-errors -std=c++11 -I/usr/lib/arm-linux-gnueabihf/openmpi/include/openmpi -I/usr/lib/arm-linux-gnueabihf/openmpi/include/openmpi/opal/mca/event/libevent2022/libevent -I/usr/lib/arm-linux-gnueabihf/openmpi/include/openmpi/opal/mca/event/libevent2022/libevent/include -I/usr/lib/arm-linux-gnueabihf/openmpi/include -pthread
INCFLAGS = -I/usr/local/include

PROJ = ExoHAI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

$(PROJ): $(OBJECTS)
	$(CC) $(DEBUG) $^ -o $@ $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) -I$(INC) $(INCFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS) $(PROJ)

