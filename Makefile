CXX = g++
CXXFLAGS = -Wall -std=c++17
SDL_FLAGS = `sdl2-config --cflags --libs`

# Ensure the build directory exists before compiling
BUILD_DIR = build
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/Snake.o $(BUILD_DIR)/Food.o $(BUILD_DIR)/Game.o

all: $(BUILD_DIR) snake

# Create the build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

snake: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/snake $(OBJECTS) $(SDL_FLAGS)

$(BUILD_DIR)/main.o: main.cpp Game.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Snake.o: Snake.cpp Snake.h
	$(CXX) $(CXXFLAGS) -c Snake.cpp -o $(BUILD_DIR)/Snake.o

$(BUILD_DIR)/Food.o: Food.cpp Food.h
	$(CXX) $(CXXFLAGS) -c Food.cpp -o $(BUILD_DIR)/Food.o

$(BUILD_DIR)/Game.o: Game.cpp Game.h Snake.h Food.h
	$(CXX) $(CXXFLAGS) -c Game.cpp -o $(BUILD_DIR)/Game.o

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/snake
