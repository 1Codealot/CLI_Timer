# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall

# Source directory, source files, and object files
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR = Final_Build
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Output executable
EXECUTABLE = $(OBJ_DIR)/CLI_Timer

.PHONY: all clean

all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the output directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)/main.o

# This ensures that the Makefile is not confused by files named 'clean' or 'all'
.SECONDARY:
