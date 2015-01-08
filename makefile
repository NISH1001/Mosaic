## Directories for include and src files
INC_DIR := include
SRC_DIR := src

## Directories to build files into
OBJ_DIR := obj
BIN_DIR := bin

## List of all c++ files to compile
CPP_FILES := $(wildcard $(SRC_DIR:%=%/*.cpp))

## List of all object files to generate
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(CPP_FILES:src/%.cpp=%.o))

## Compiler and linker flags and libraries to use
CC := g++
LDLIBS := -lSDL2
FLAGS := -I$(INC_DIR)/ --std=c++11


## Build files

all: output

output: $(OBJ_FILES)
	$(CC) -o $@ $^ line.cpp $(LDLIBS) $(FLAGS)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(LDLIBS) $(FLAGS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm $(OBJ_DIR)/*.o
