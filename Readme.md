- Build for windows:
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows

 - In case of erros by not fiding main function, in the file "SDL_main.h" inside the condition "#if defined(SDL_MAIN_NEEDED) || defined(SDL_MAIN_AVAILABLE"
 
 add this:
 
#define main SDL_main    //Original line. Renames main(){} to SDL_main(){}. 

#define main main        //Added line. Undo the renaming.

reference: https://stackoverflow.com/questions/33400777/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-int-cde/62825741#62825741
