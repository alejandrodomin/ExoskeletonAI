CC = mpic++
SRC := src
OBJ := build
INC := include

DEBUG = -g
LFLAGS = -llsm9ds1
CFLAGS = -Wfatal-errors -std=c++11

PROJ = ExoHAI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

$(PROJ): $(OBJECTS)
	$(CC) $(DEBUG) $^ -o $@ $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm $(OBJECTS) $(PROJ)