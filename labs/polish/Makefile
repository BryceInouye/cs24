CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

all: test

test: AST.cpp Nodes.cpp Stack.cpp main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
	
valgrind: test
	valgrind --leak-check=full ./test

clean:
	rm -f test

.PHONY: all clean
