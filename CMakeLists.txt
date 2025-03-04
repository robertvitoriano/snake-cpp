cmake_minimum_required(VERSION 3.10)
project(SnakeGame CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Directories
set(SRC_DIR src)
set(INC_DIR include windows-libraries/include)
set(LIB_DIR windows-libraries/lib)

# Collect source files
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

# Define executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

# Link directories
target_link_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})

# Link libraries for MinGW
target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_mixer SDL2_ttf SDL2_image)
