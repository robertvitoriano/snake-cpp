#!/bin/bash

# Create directories for third-party libraries
mkdir -p ./thirdparty/nlohmann
mkdir -p ./thirdparty/sdl2/include
mkdir -p ./thirdparty/sdl2_image/include
mkdir -p ./thirdparty/sdl2_mixer/include
mkdir -p ./thirdparty/sdl2_ttf/include

# Download nlohmann JSON library
wget -O ./thirdparty/nlohmann/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
echo "nlohmann/json.hpp downloaded successfully!"

# Download SDL2 (you'll need to download the appropriate files from the SDL2 website or package)
wget -O ./thirdparty/sdl2/include/SDL2/SDL.h https://raw.githubusercontent.com/libsdl-org/SDL/main/include/SDL2/SDL.h
# Similarly download the rest of SDL2 and its extensions
# SDL2_image
wget -O ./thirdparty/sdl2_image/include/SDL2/SDL_image.h https://raw.githubusercontent.com/libsdl-org/SDL_image/main/include/SDL2/SDL_image.h
# SDL2_mixer
wget -O ./thirdparty/sdl2_mixer/include/SDL2/SDL_mixer.h https://raw.githubusercontent.com/libsdl-org/SDL_mixer/main/include/SDL2/SDL_mixer.h
# SDL2_ttf
wget -O ./thirdparty/sdl2_ttf/include/SDL2/SDL_ttf.h https://raw.githubusercontent.com/libsdl-org/SDL_ttf/main/include/SDL2/SDL_ttf.h

echo "SDL2 libraries downloaded successfully!"
