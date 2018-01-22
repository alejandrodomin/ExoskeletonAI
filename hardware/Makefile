CC = gcc
SRC := src
OBJ := build
INC := include

PROJ = ExoHAI

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

$(PROJ): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(INC) -c $< -o $@

clean:
	rm build/*.o $(PROJ)