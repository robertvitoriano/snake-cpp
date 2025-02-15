cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

# Detect OS and set SDL2 directory
if(WIN32)
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/thirdparty/sdl2-win")
    # For Windows, use MinGW toolchain
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/mingw-w64-x86_64.cmake")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build-win)
else()
    set(SDL2_DIR "/usr")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build-linux)
endif()

# Include directories
include_directories(include)
include_directories(thirdparty/nlohmann)
include_directories(${SDL2_DIR}/include)

# Find SDL2 libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Collect source files
file(GLOB SRC "src/*.cpp" "src/*.c")

# Add executable
add_executable(SnakeGame ${SRC})

# Set output name for the executable
if(WIN32)
    set_target_properties(SnakeGame PROPERTIES OUTPUT_NAME "SnakeGame.exe")
else()
    set_target_properties(SnakeGame PROPERTIES OUTPUT_NAME "SnakeGame.out")
endif()

# Link libraries for SDL2
target_link_libraries(SnakeGame 
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)

# On Windows, make sure we are linking SDL2 correctly if needed
if(WIN32)
    target_link_libraries(SnakeGame 
        ${SDL2_DIR}/lib/SDL2main.a
        ${SDL2_DIR}/lib/SDL2.a
        ${SDL2_DIR}/lib/SDL2_image.a
        ${SDL2_DIR}/lib/SDL2_mixer.a
        ${SDL2_DIR}/lib/SDL2_ttf.a
    )
endif()
