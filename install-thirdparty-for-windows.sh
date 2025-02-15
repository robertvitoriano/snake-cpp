#!/bin/bash

# Create directories for third-party libraries
mkdir -p ./thirdparty/nlohmann
mkdir -p ./thirdparty/sdl2-win


# # Download nlohmann JSON library
wget -O ./thirdparty/nlohmann/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
echo "nlohmann/json.hpp downloaded successfully!"

# Download SDL2 (you'll need to download the appropriate files from the SDL2 website or package)
wget -O sdl2-mingw.tar.gz https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-mingw.tar.gz
tar -xzf sdl2-mingw.tar.gz -C thirdparty/sdl2-win --strip-components=1

wget -O sdl2-image-mingw.tar.gz https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-devel-2.6.3-mingw.tar.gz
tar -xzf sdl2-image-mingw.tar.gz -C thirdparty/sdl2-win --strip-components=1

wget -O sdl2-mixer-mingw.tar.gz https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-devel-2.6.3-mingw.tar.gz
tar -xzf sdl2-mixer-mingw.tar.gz -C thirdparty/sdl2-win --strip-components=1

wget -O sdl2-ttf-mingw.tar.gz https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-mingw.tar.gz
tar -xzf sdl2-ttf-mingw.tar.gz -C thirdparty/sdl2-win --strip-components=1

rm -v ./sdl2-mingw.tar.gz ./sdl2-image-mingw.tar.gz ./sdl2-mixer-mingw.tar.gz ./sdl2-ttf-mingw.tar.gz

echo "SDL2 libraries downloaded successfully!"

