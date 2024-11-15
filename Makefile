CXX = g++
CXXFLAGS = -Wall -std=c++17
SDL_FLAGS = `sdl2-config --cflags --libs`

# Ensure the build directory exists before compiling
BUILD_DIR = build
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/Paddle.o $(BUILD_DIR)/Ball.o $(BUILD_DIR)/Game.o

all: $(BUILD_DIR) pong

# Create the build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

pong: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/pong $(OBJECTS) $(SDL_FLAGS)

$(BUILD_DIR)/main.o: main.cpp Game.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Paddle.o: Paddle.cpp Paddle.h
	$(CXX) $(CXXFLAGS) -c Paddle.cpp -o $(BUILD_DIR)/Paddle.o

$(BUILD_DIR)/Ball.o: Ball.cpp Ball.h
	$(CXX) $(CXXFLAGS) -c Ball.cpp -o $(BUILD_DIR)/Ball.o

$(BUILD_DIR)/Game.o: Game.cpp Game.h Paddle.h Ball.h
	$(CXX) $(CXXFLAGS) -c Game.cpp -o $(BUILD_DIR)/Game.o

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/pong
