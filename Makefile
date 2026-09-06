# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

# Target Executable Name
TARGET = taskforge

# Directories
SRC_DIR = .
OBJ_DIR = obj

# Source and Object Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsub Dust/$(SRCS:.cpp=.o), $(OBJ_DIR)/%)
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# Default Rule
all: $(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile Source Files to Object Files
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create Object Directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean Build Artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean