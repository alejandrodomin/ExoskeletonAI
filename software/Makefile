CC = mpic++
SRC := src
MSRC := main
OBJ := build
INC := include

DEBUG = -g
LFLAGS = -lboost_thread -lboost_system
CFLAGS = -Wfatal-errors -std=c++11

PROJ = ExoSAI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

MSOURCES := $(wildcard $(MSRC)/*.cpp)
MOBJECTS := $(patsubst $(MSRC)/%.cpp, $(OBJ)/%.o, $(MSOURCES))

$(PROJ): $(OBJECTS) $(MOBJECTS)
	$(CC) $(DEBUG) $^ -o $@ $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) -I$(INC) -c $< -o $@

$(OBJ)/%.o: $(MSRC)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm $(OBJECTS) $(MOBJECTS) $(PROJ)
