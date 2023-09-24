cmake_minimum_required(VERSION 3.27)
project(Bang)

file(GLOB BangLibSources src/BangLib/*.cc)
add_library(Bang STATIC ${BangLibSources})
target_include_directories(Bang PUBLIC "include/BangLib")
set_property(TARGET Bang PROPERTY CXX_STANDARD 17)

file(GLOB BangSources src/*.cc)

add_executable(BangGame ${BangSources})
find_library(SDLLibPath SDL2 "/usr/lib")
find_library(SDL_IMGLibPath SDL2_image "usr/lib/")
find_library(SDL_TTFLibPath SDL2_ttf "usr/lib/")
target_link_libraries(BangGame PUBLIC Bang ${SDLLibPath})
target_link_libraries(BangGame PUBLIC Bang ${SDL_IMGLibPath})
target_link_libraries(BangGame PUBLIC Bang ${SDL_TTFLibPath})
target_include_directories(BangGame PUBLIC "include/")
target_include_directories(BangGame PUBLIC "usr/include/")
set_property(TARGET BangGame PROPERTY CXX_STANDARD 17)

set_target_properties(Bang PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(BangGame PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
