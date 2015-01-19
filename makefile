## Directories for include and src files
INC_DIR := include
SRC_DIR := src

## Directories to build files into
OBJ_DIR := obj
BIN_DIR := bin

## List of all c++ files to compile
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
INC_FILES := $(wildcard $(INC_DIR)/*.h)

## List of all object files to generate
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(CPP_FILES:$(SRC_DIR)/%.cpp=%.o))

## Compiler and linker flags and libraries to use
<<<<<<< HEAD
##CC := clang++
CC := g++
CXXLIBS := 
LDLIBS := -lSDL2
CXXFLAGS := -I$(INC_DIR) -std=c++11 -MMD $(CXXLIBS) -O3
LDFLAGS := --std=c++11 $(LDLIBS)
=======
CC := clang++
##CC := g++
CXXLIBS := 
LDLIBS := -lSDL2
CXXFLAGS := -I $(INC_DIR) -std=c++11 -MMD $(CXXLIBS) -O3
LDFLAGS := --std=c++11 $(LDLIBS)

>>>>>>> past

## Build files

all: bin/output

$(BIN_DIR)/output: $(OBJ_FILES) | $(BIN_DIR) 
<<<<<<< HEAD
	$(CC) -o $@ $^ $(LDFLAGS) -I$(INC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CXXFLAGS)
=======
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -c -o $@ $<  $(CXXFLAGS)
>>>>>>> past

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm -rf obj
<<<<<<< HEAD

#include auto generated dependencies 
=======
	rm -rf bin

## Include auto-generated dependencies rules
>>>>>>> past
-include $(OBJ_FILES:.o=.d)
