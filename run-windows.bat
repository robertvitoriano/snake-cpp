@echo off
cd "build"

:: Run CMake configuration
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows

:: Build the project
cmake --build .

cd .. 

:: Create "windows-build" folder if it doesn't exist
if not exist "windows-build" mkdir "windows-build"

:: Copy built files from Debug folder to "windows-build"
xcopy /E /Y "Debug\*" "windows-build\"

:: Copy "assets" folder and its assetss to "windows-build"
xcopy /E /Y "assets" "windows-build\assets"

:: Copy levels.json to "windows-build"
copy /Y "levels.json" "windows-build\"

:: Navigate to "windows-build" and run the game
cd "windows-build"

"SnakeGame.out.exe"
