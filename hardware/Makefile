CC = c++
SRC := src
OBJ := build
INC := include

PROJ = ExoHAI

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

$(PROJ): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -I$(INC) -c $< -o $@

clean:
	rm build/*.o $(PROJ)