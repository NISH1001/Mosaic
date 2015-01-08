SRC_DIR := src
OBJ_DIR := obj
PPS := $(wildcard $(SRC_DIR:%=%/*.cpp))
CPPS = src/Circle.cpp src/Line.cpp src/Ellipse.cpp
OBJS := $(addprefix $(OBJ_DIR)/, $(CPPS:src/%.cpp=%.o))
FLAGS := -lSDL2 -Iinclude/ --std=c++11

all:  output

output: pixel.o point.o line.o circle.o ellipse.o point.o transform.o
	clang++ -o $@ line.cpp *.o $(FLAGS)
pixel.o:
	clang++ -c -o $@ src/pixel.cpp $(FLAGS)
point.o:
	clang++ -c -o $@ src/Point2D.cpp $(FLAGS)
line.o: 
	clang++ -c -o $@ src/Line.cpp pixel.o $(FLAGS)
circle.o:
	clang++ -c -o $@ src/Circle.cpp pixel.o $(FLAGS)
ellipse.o:
	clang++ -c -o $@ src/Ellipse.cpp pixel.o $(FLAGS)
point.o:
	clang++ -c -o $@ src/Point2D.cpp pixel.o $(FLAGS)
transform.o:
	clang++ -c -o $@ src/Transform.cpp pixel.o $(FLAGS)
$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR) 
	clang++ -c -o $@ $<  $(FLAGS)
$(OBJ_DIR):
	mkdir $(OBJ_DIR) 
clean:
	rm *.o
