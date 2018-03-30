CC = mpic++
SRC := ../software/src
INC := ../software/include
WXSRC := src
WXINC := include
OBJ := build

DEBUG = -g

LFLAGS = -lboost_thread -lboost_system
CFLAGS = -Wfatal-errors -std=c++11

WXLFLAGS = $(shell wx-config --libs all)
WXCFLAGS = $(shell wx-config --cxxflags)

PROJ = ExoGUI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

WXSOURCES := $(wildcard $(WXSRC)/*.cpp)
WXOBJECTS := $(patsubst $(WXSRC)/%.cpp, $(OBJ)/%.o, $(WXSOURCES))

$(PROJ): $(OBJECTS) $(WXOBJECTS)
	$(CC) $(DEBUG) $^ $(WXLFLAGS) -o $@ $(LFLAGS)

ifeq ($(SOFTWARE), "1")
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(WXCFLAGS) $(DEBUG) $(CFLAGS) -I$(INC) -I$(WXINC) -c $< -o $@
endif

$(OBJ)/%.o: $(WXSRC)/%.cpp
	$(CC) $(WXCFLAGS) $(DEBUG) $(CFLAGS) -I$(INC) -I$(WXINC) -c $< -o $@

clean:
	rm $(OBJECTS) $(WXOBJECTS) $(PROJ)
