@echo off
REM Create directories for third-party libraries
mkdir .\thirdparty\nlohmann
mkdir .\thirdparty\sdl2\include
mkdir .\thirdparty\sdl2_image\include
mkdir .\thirdparty\sdl2_mixer\include
mkdir .\thirdparty\sdl2_ttf\include

REM Download nlohmann JSON library
curl -L -o .\thirdparty\nlohmann\json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
echo "nlohmann/json.hpp downloaded successfully!"

REM Download SDL2 (you'll need to download the appropriate files from the SDL2 website or package)
curl -L -o .\thirdparty\sdl2\include\SDL2\SDL.h https://raw.githubusercontent.com/libsdl-org/SDL/main/include/SDL2/SDL.h

REM Similarly download the rest of SDL2 and its extensions
REM SDL2_image
curl -L -o .\thirdparty\sdl2_image\include\SDL2\SDL_image.h https://raw.githubusercontent.com/libsdl-org/SDL_image/main/include/SDL2/SDL_image.h

REM SDL2_mixer
curl -L -o .\thirdparty\sdl2_mixer\include\SDL2\SDL_mixer.h https://raw.githubusercontent.com/libsdl-org/SDL_mixer/main/include/SDL2/SDL_mixer.h

REM SDL2_ttf
curl -L -o .\thirdparty\sdl2_ttf\include\SDL2\SDL_ttf.h https://raw.githubusercontent.com/libsdl-org/SDL_ttf/main/include/SDL2/SDL_ttf.h

echo "SDL2 libraries downloaded successfully!"
pause
