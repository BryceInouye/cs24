censor: censor.o
	g++ -std=c++17 -g -Wall -Wextra -Werror -Wno-unused-parameter censor.o -o censor

censor.o: censor.cpp
	g++ -std=c++17 -g -Wall -Wextra -Werror -Wno-unused-parameter -c censor.cpp

valgrind: censor
	valgrind --leak-check=full ./censor $(ARGS)

clean:
	rm *.o censor