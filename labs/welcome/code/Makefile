output: censor.o
	g++ -std=c++17 -g -Wall -Wextra -Werror -Wno-unused-parameter censor.o -o output

censor.o: censor.cpp
	g++ -std=c++17 -g -Wall -Wextra -Werror -Wno-unused-parameter -c censor.cpp

valgrind: output
	valgrind --leak-check=full ./output $(ARGS)

clean:
	rm *.o output