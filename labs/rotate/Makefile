CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = test.cpp Tree.cpp Node.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = test

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)




