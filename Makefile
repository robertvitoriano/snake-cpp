CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -I/usr/include/SDL2
SDL_FLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf

BUILD_DIR = build
SRC_DIR = src
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/Snake.o $(BUILD_DIR)/Food.o $(BUILD_DIR)/Score.o $(BUILD_DIR)/Game.o $(BUILD_DIR)/Renderer.o $(BUILD_DIR)/MusicPlayer.o

all: $(BUILD_DIR) snake

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

snake: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/snake $(OBJECTS) $(SDL_FLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/Game.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Snake.o: $(SRC_DIR)/Snake.cpp $(SRC_DIR)/Snake.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Snake.cpp -o $(BUILD_DIR)/Snake.o

$(BUILD_DIR)/Food.o: $(SRC_DIR)/Food.cpp $(SRC_DIR)/Food.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Food.cpp -o $(BUILD_DIR)/Food.o
	
$(BUILD_DIR)/Score.o: $(SRC_DIR)/Score.cpp $(SRC_DIR)/Score.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Score.cpp -o $(BUILD_DIR)/Score.o

$(BUILD_DIR)/Renderer.o: $(SRC_DIR)/Renderer.cpp $(SRC_DIR)/Renderer.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Renderer.cpp -o $(BUILD_DIR)/Renderer.o
	
$(BUILD_DIR)/MusicPlayer.o: $(SRC_DIR)/MusicPlayer.cpp $(SRC_DIR)/MusicPlayer.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/MusicPlayer.cpp -o $(BUILD_DIR)/MusicPlayer.o

$(BUILD_DIR)/Game.o: $(SRC_DIR)/Game.cpp $(SRC_DIR)/Game.h $(SRC_DIR)/Snake.h $(SRC_DIR)/Food.h  $(SRC_DIR)/Score.h $(SRC_DIR)/Renderer.h $(SRC_DIR)/MusicPlayer.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Game.cpp -o $(BUILD_DIR)/Game.o

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/snake
