CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS =

# List of source files
GAME_CHECK_SRC = game-check.cpp
MOVE_CHECK_SRC = move-check.cpp
BOARD_SRC = Board.cpp
MOVE_SRC = Move.cpp

# List of object files
GAME_CHECK_OBJ = $(GAME_CHECK_SRC:.cpp=.o)
MOVE_CHECK_OBJ = $(MOVE_CHECK_SRC:.cpp=.o)
BOARD_OBJ = $(BOARD_SRC:.cpp=.o)
MOVE_OBJ = $(MOVE_SRC:.cpp=.o)

# Executables
GAME_CHECK_EXEC = game-check
MOVE_CHECK_EXEC = move-check

# Targets
all: $(GAME_CHECK_EXEC) $(MOVE_CHECK_EXEC)

$(GAME_CHECK_EXEC): $(GAME_CHECK_OBJ) $(BOARD_OBJ) $(MOVE_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(MOVE_CHECK_EXEC): $(MOVE_CHECK_OBJ) $(MOVE_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(GAME_CHECK_OBJ) $(MOVE_CHECK_OBJ) $(BOARD_OBJ) $(MOVE_OBJ) $(GAME_CHECK_EXEC) $(MOVE_CHECK_EXEC)

.PHONY: all clean




# CXX = g++              (old makefile)
# CXXFLAGS = -std=c++11 -Wall -Wextra

# SRCS = move-tests.cpp Move.cpp
# OBJS = $(SRCS:.cpp=.o)
# TARGET = move-tests

# .PHONY: all clean

# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS) $(TARGET)
