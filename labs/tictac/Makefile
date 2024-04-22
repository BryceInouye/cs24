CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = move-tests.cpp Move.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = move-tests

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
