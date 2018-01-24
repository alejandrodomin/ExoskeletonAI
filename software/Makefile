CC = c++
SRC := src
OBJ := build
INC := include

LFLAGS = -pthread
CFLAGS = -std=c++11 

PROJ = ExoSAI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

$(PROJ): $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm build/*.o $(PROJ)