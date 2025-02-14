cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(include /usr/include)
include_directories(thirdparty/nlohmann)
include_directories(thirdparty/sdl2/include)
include_directories(thirdparty/sdl2_image/include)
include_directories(thirdparty/sdl2_mixer/include)
include_directories(thirdparty/sdl2_ttf/include)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB SRC "src/*.cpp" "src/*.c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(SnakeGame ${SRC})

set_target_properties(SnakeGame PROPERTIES OUTPUT_NAME "SnakeGame.out")

target_link_libraries(SnakeGame 
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)
