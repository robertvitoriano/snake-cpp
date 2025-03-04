@echo off
cd "build"

:: Run CMake configuration
cmake -G "MinGW Makefiles" ..

:: Build the project
cmake --build .

cd .. 

:: Create "windows-build" folder if it doesn't exist
if not exist "windows-build" mkdir "windows-build"

:: Copy built files from Debug folder to "windows-build"
xcopy /Y "build\SnakeGame.exe" "windows-build\"

:: Copy "assets" folder and its assetss to "windows-build"
xcopy /E /Y "assets" "windows-build\assets"

:: Copy levels.json to "windows-build"
copy /Y "levels.json" "windows-build\"

:: Navigate to "windows-build" and run the game
cd "windows-build"

"SnakeGame.exe"
