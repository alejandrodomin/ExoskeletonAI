CC = mpic++
SRC := src
OBJ := build
INC := include

DEBUG = -g

LFLAGS = -lboost_thread -lboost_system
CFLAGS = -Wfatal-errors -std=c++11

WXLFLAGS = $(shell wx-config --libs all)
WXCFLAGS = $(shell wx-config --cxxflags)

PROJ = ExoGUI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

$(PROJ): $(OBJECTS)
	$(CC) $(DEBUG) $^ $(WXLFLAGS) -o $@ $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(WXCFLAGS) $(DEBUG) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm $(OBJECTS) $(PROJ)
