cmake_minimum_required(VERSION 3.10)
project(SnakeGame CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Directories
set(SRC_DIR src)
if(WIN32)
  set(INC_DIR include windows-libraries/include)
  set(LIB_DIR windows-libraries/lib)
else()
  set(INC_DIR include usr/include)
endif()

# Collect source files
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

# Define executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

# Link directories
target_link_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})

if(WIN32)
  target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_mixer SDL2_ttf SDL2_image)
else()
  target_link_libraries(${PROJECT_NAME}  
      SDL2::SDL2
      SDL2_image::SDL2_image
      SDL2_mixer::SDL2_mixer
      SDL2_ttf::SDL2_ttf
      nlohmann_json::nlohmann_json
  )
endif()
