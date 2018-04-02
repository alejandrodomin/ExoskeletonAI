CC = mpic++

OBJ := build
PROJ = ExoAI

SSRC := software/src
HSRC := hardware/src

SINC := software/include
HINC := hardware/include

ifeq ($(GUI), "1")
GSRC := gui/src
GINC := gui/include
endif

CFLAGS = -Wall -Wfatal-errors -std=c++11
LFLAGS = -lboost_thread -lboost_system -llsm9ds1 -lwiringPi

ifeq ($(GUI), "1")
CFLAGS += $(shell wx-config --cxxflags)
LFLAGS += $(shell wx-config --libs all)

GSOURCES := $(wildcard $(GSRC)/*.cpp)
GOBJECTS := $(patsubst $(GSRC)/%.cpp, $(OBJ)/%.o, $(GSOURCES))
endif

SSOURCES := $(wildcard $(SSRC)/*.cpp)
SOBJECTS := $(patsubst $(SSRC)/%.cpp, $(OBJ)/%.o, $(SSOURCES))

HSOURCES := $(wildcard $(HSRC)/*.cpp)
HOBJECTS := $(patsubst $(HSRC)/%.cpp, $(OBJ)/%.o, $(HSOURCES))

MSOURCES := $(wildcard software/main/*.cpp)
MOBJECTS := $(patsubst software/main/%.cpp, $(OBJ)/%.o, $(MSOURCES))

$(PROJ): $(SOBJECTS) $(HOBJECTS) $(MOBJECTS)
	$(CC) $(DEBUG) $^ -o $@ $(LFLAGS)

$(OBJ)/%.o: $(SSRC)/%.cpp
	$(CC) $(CFLAGS) -I$(SINC) -I$(HINC) -c $< -o $@

$(OBJ)/%.o: $(HSRC)/%.cpp
	$(CC) $(CFLAGS) -I$(SINC) -I$(HINC) -c $< -o $@

ifeq ($(GUI), "1")
$(OBJ)/%.o: $(GSRC)/%.cpp
	$(CC) $(CFLAGS) -I$(GINC) -I$(SINC) -I$(HINC) -c $< -o $@
endif

$(OBJ)/%.o: software/main/*.cpp
	$(CC) $(CFLAGS) -I$(SINC) -I$(HINC) -c $< -o $@

clean:
	rm $(SOBJECTS) $(HOBJECTS) $(GOBJECTS) $(PROJ)
