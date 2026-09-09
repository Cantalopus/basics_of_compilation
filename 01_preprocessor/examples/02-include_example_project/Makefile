SRC = $(wildcard src/app/*.cpp src/numbers/*.cpp)
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

CXX ?= g++
CPPFLAGS = -MMD -MP -Isrc/numbers
CXXFLAGS = -std=c++20 -Wall -Wextra 
LDFLAGS = 

.PHONY: all run clean inc

all: bin/main

bin/main: $(OBJ)
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

#.PHONY: run
run: bin/main
	./bin/main

#.PHONY: clean
clean:
	rm -rf build
	rm -rf bin

#.PHONY: inc
inc: 
	ln -sfn ./build/default/compile_commands.json compile_commands.json
