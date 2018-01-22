CC = gcc
SRC := src
OBJ := build
INC := include

LDFLAGS = -lm

PROJ = ExoHAI

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

$(PROJ): $(OBJECTS)
	$(CC) $(LDFLAGS)  $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(INC) -c $< -o $@

clean:
	rm build/*.o $(PROJ)
