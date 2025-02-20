@echo off
cd /d "%~dp0\build"

:: Run CMake configuration
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows
if %errorlevel% neq 0 (
    echo CMake configuration failed.
    exit /b %errorlevel%
)

:: Build the project
cmake --build .
if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
)

:: Go back to the root directory
cd ..

:: Copy all files from the Debug folder to the root
xcopy /E /Y "Debug\*" .

:: Run the generated executable
"SnakeGame.out.exe"
