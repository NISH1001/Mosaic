
all: obj/main.o obj/primitives.o obj/point2d.o obj/line.o
	g++ obj/main.o obj/primitives.o obj/point2d.o obj/line.o -o output -lSDL2 -Iinclude/ -std=c++11

obj/main.o: main.cpp
	g++ -c main.cpp -o $@ -Iinclude/ -std=c++11

obj/primitives.o: src/Primitives.cpp
	g++ -c src/Primitives.cpp -o $@ -Iinclude/ -std=c++11

obj/point2d.o: src/Point2D.cpp
	g++ -c src/Point2D.cpp -o $@ -Iinclude/ -std=c++11

obj/line.o: src/Line.cpp
	g++ -c src/Line.cpp -o $@ -Iinclude/ -std=c++11

clean:
	rm *.o
