main: build/main.o
	g++ build/main.o -o bin/main

build/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

# :all builds main.i for purposes of this demonstration
.PHONY: all
all: build/main.i

build/main.i: src/main.cpp
	g++ -E src/main.cpp > build/main.i


.PHONY: clean
clean: 
	rm -rf bin/main
	rm -rf ./build
	rm -rf ./bin
	mkdir ./build
	mkdir ./bin
