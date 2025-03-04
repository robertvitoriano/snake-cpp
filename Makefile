# Directories
SRC_DIR := src
INC_DIR := include windows-libraries/include
LIB_DIR := windows-libraries/lib

# Compiler
CXXFLAGS := $(addprefix -I, $(INC_DIR)) -std=c++17 

# Output
TARGET := main

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# Linker flags (added -lSDL2_ttf -lSDL2_image)
LDFLAGS := $(addprefix -L, $(LIB_DIR)) -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilation
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ_FILES) $(TARGET)
