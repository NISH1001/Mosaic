## Directories for include and src files
INC_DIR := include
SRC_DIR := src

## Directories to build files into
OBJ_DIR := obj
BIN_DIR := bin

## List of all c++ files to compile
CPP_FILES := $(wildcard $(SRC_DIR:%=%/*.cpp))
INC_FILES := $(wildcard $(INC_DIR:%=%/*.h))

## List of all object files to generate
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(CPP_FILES:src/%.cpp=%.o))

## Compiler and linker flags and libraries to use
CC := clang++
##CC := g++
LDLIBS := -lSDL2
FLAGS := -I$(INC_DIR)/ --std=c++11 -O3


## Build files

all: bin/output

bin/output: $(OBJ_FILES) | $(BIN_DIR) 
	$(CC) -o $@ $^ test.cpp $(LDLIBS) $(FLAGS)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(LDLIBS) $(FLAGS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm $(OBJ_DIR)/*.o
