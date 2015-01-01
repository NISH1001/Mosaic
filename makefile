
all: primitives.o
	g++ main.cpp -o output -lSDL2 -Iinclude/

primitives.o: 
	g++ -c src/primitives.cpp -o $@ -Iinclude/

clean:
	rm *.o
