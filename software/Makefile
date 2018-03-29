CC = mpic++

SRC := src
MSRC := main
HSRC := ../hardware/src

OBJ := build
INC := include
HINC := 

DEBUG = -g
LFLAGS = -lboost_thread -lboost_system -llsm9ds1
CFLAGS = -Wall -std=c++11 
PROJ = ExoSAI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

SOURCES += $(wildcard $(MSRC)/*.cpp)
OBJECTS += $(patsubst $(MSRC)/%.cpp, $(OBJ)/%.o, $(MSOURCES))

ifeq ($(HARDWARE),"1")
	SOURCES += $(wildcard $(HSRC)/*.cpp)
	OBJECTS += $(patsubst $(HSRC)/%.cpp, $(OBJ)/%.o, $(HSOURCES))

	HINC = ../hardware/include
else
endif

$(PROJ): $(OBJECTS) $(MOBJECTS)
	$(CC) $(DEBUG) $^ -o $@ $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) -I$(INC) -I$(HINC) -c $< -o $@

$(OBJ)/%.o: $(MSRC)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) -I$(INC) -I$(HINC) -c $< -o $@

clean:
	rm $(OBJECTS) $(MOBJECTS) $(PROJ)
