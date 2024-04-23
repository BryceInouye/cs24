# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source and object files
GAMECHECK_SRC = game-check.cpp Board.cpp Move.cpp
GAMECHECK_OBJ = $(GAMECHECK_SRC:.cpp=.o)

# Target
GAMECHECK = game-check

# Phony targets
.PHONY: all clean gamecheck

# Build all targets
all: gamecheck

# Build gamecheck
gamecheck: $(GAMECHECK_OBJ)
	$(CXX) $(CXXFLAGS) -o $(GAMECHECK) $(GAMECHECK_OBJ)

# Compile individual source file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove object files and executable
clean:
	rm -f $(GAMECHECK_OBJ) $(GAMECHECK)



# CXX = g++
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