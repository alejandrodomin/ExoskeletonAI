CC = mpic++

OBJ := build
PROJ = ExoAI

SSRC := software/src
HSRC := hardware/src
ifeq ($(GUI),"1")
GSRC := gui/src
endif

SINC := software/include
HINC := hardware/include
ifeq ($(GUI), "1")
GINC := gui/include
endif

CFLAGS = -Wall -std=c++11
LFLAGS = -lboost_thread -lboost_system -llsm9ds1

SSOURCES := $(wildcard $(SSRC)/*.cpp)
SOBJECTS := $(patsubst $(SSRC)/%.cpp, $(OBJ)/%.o, $(SSOURCES))

HSOURCES := $(wildcard $(HSRC)/*.cpp)
HOBJECTS := $(patsubst $(HSRC)/%.cpp, $(OBJ)/%.o, $(HSOURCES))

$(PROJ): $(SOBJECTS) $(HOBJECTS)
	$(CC) $(DEBUG) $^ -o $@ $(LFLAGS)

$(OBJ)/%.o: $(SSRC)/%.cpp
	$(CC) $(CFLAGS) -I$(SINC) -I$(HINC) -c $< -o $@

$(OBJ)/%.o: $(HSRC)/%.cpp
	$(CC) $(CFLAGS) -I$(SINC) -I$(HINC) -c $< -o $@

clean:
	rm $(SOBJECTS) $(HOBJECTS) $(PROJ)
