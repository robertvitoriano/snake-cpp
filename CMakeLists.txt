cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

if(DEFINED CMAKE_TOOLCHAIN_FILE AND EXISTS ${CMAKE_TOOLCHAIN_FILE})
    message(STATUS "Using vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
    include_directories(${CMAKE_SOURCE_DIR}/include)
else()
    message(STATUS "No vcpkg toolchain detected, using system packages")
    include_directories(include /usr/include)

endif()



find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB SRC "src/*.cpp" "src/*.c")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(SnakeGame ${SRC})

set_target_properties(SnakeGame PROPERTIES OUTPUT_NAME "SnakeGame.out")

target_link_libraries(SnakeGame 
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    nlohmann_json::nlohmann_json
)
