# Build Instructions (Windows)

## Prerequisites
Ensure you have the following installed:
- [CMake](https://cmake.org/download/)
- [Visual Studio 2022](https://visualstudio.microsoft.com/) (with C++ development tools)
- [vcpkg](https://github.com/microsoft/vcpkg) (for package management)

## Install libraries:
```sh
    vcpkg install nlohmann-json sdl2 sdl2-image sdl2-mixer sdl2-ttf
```

## Building the Project
To build the project using CMake and Visual Studio, run the following command inside your build directory:

```sh
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows
```

This will generate the necessary Visual Studio solution files for compilation.

## Fix for Missing `main` Function (SDL)
If you encounter an **"unresolved external symbol main"** error while linking, you may need to adjust `SDL_main.h`.

### Solution
Inside the `SDL_main.h` file, locate the following condition:

```c
#if defined(SDL_MAIN_NEEDED) || defined(SDL_MAIN_AVAILABLE)
```

Modify the section by adding the following lines:

```c
#define main SDL_main  // Original line: Renames main(){} to SDL_main(){}.
#define main main      // Added line: Undoes the renaming.
```

### Reference
For more details on this issue, refer to this [Stack Overflow post](https://stackoverflow.com/a/62825741/62825741).

