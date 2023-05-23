CXX = g++
CXXFLAGS = -Wall -pedantic pkg-config --cflags gtkmm-3.0
LDFLAGS = pkg-config --libs gtkmm-3.0
EXEC = projet

# List of source files
SRCS = main.cpp graph.cpp scoreboard.cpp 

# List of object files
OBJS = $(SRCS:.cpp=.o)

# Default target: the program
all: $(EXEC)

# Compilation rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for creating the program
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXEC)

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)