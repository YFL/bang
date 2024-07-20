cmake_minimum_required(VERSION 3.27)
project(Bang)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_library(SDLLibPath SDL2 "external/SDL2-2.30.3/lib/x64")
find_library(SDL_IMGLibPath SDL2_image "external/SDL2_image-2.8.2/lib/x64")
find_library(SDL_TTFLibPath SDL2_ttf "external/SDL2_ttf-2.22.0/lib/x64")
find_library(jsonppLibPath jsoncpp_static external/jsoncpp/build/lib/Release)

file(GLOB BangLibSources src/BangLib/*.cc include/BangLib/*.h)
add_library(Bang STATIC ${BangLibSources})
target_include_directories(Bang PUBLIC "include/BangLib")
target_include_directories(Bang PUBLIC "include/UtilsLib")
target_include_directories(Bang PUBLIC "include/SDLUtilsLib")
target_include_directories(Bang PUBLIC "external/jsoncpp/include")
target_include_directories(Bang PUBLIC "external/SDL2-2.30.3/include")
target_include_directories(Bang PUBLIC "external/SDL2_image-2.8.2/include")
target_include_directories(Bang PUBLIC "external/SDL2_ttf-2.22.0/include")
set_property(TARGET Bang PROPERTY CXX_STANDARD 20)

file(GLOB UtilsLibSources src/UtilsLib/*.cc include/UtilsLib/*.h)
add_library(Utils SHARED ${UtilsLibSources})
target_include_directories(Utils PUBLIC "include/UtilsLib")
target_include_directories(Utils PUBLIC "external/SDL2-2.30.3/include")
target_include_directories(Utils PUBLIC "external/SDL2_image-2.8.2/include")
target_include_directories(Utils PUBLIC "external/SDL2_ttf-2.22.0/include")
target_include_directories(Utils PUBLIC "external/jsoncpp/include")
target_link_libraries(Utils PUBLIC ${jsonppLibPath})
set_property(TARGET Utils PROPERTY CXX_STANDARD 20)
set_property(TARGET Utils PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

file(GLOB GraphicsLibSources src/GraphicsLib/*.cc include/GraphicsLib/*.h)
add_library(Graphics SHARED ${GraphicsLibSources})
target_include_directories(Graphics PUBLIC "include/GraphicsLib")
target_include_directories(Graphics PUBLIC "include/UtilsLib")
target_include_directories(Graphics PUBLIC "include/SDLUtilsLib")
target_include_directories(Graphics PUBLIC "external/SDL2-2.30.3/include")
target_link_libraries(Graphics PUBLIC Utils)
set_property(TARGET Graphics PROPERTY CXX_STANDARD 20)

file(GLOB SDLUtilsLibSources src/SDLUtilsLib/*.cc include/SDLUtilsLib/*.h)
add_library(SDLUtils SHARED ${SDLUtilsLibSources})
target_include_directories(SDLUtils PUBLIC "include/SDLUtilsLib")
target_include_directories(SDLUtils PUBLIC "include/UtilsLib")
target_include_directories(SDLUtils PUBLIC "external/SDL2-2.30.3/include")
target_include_directories(SDLUtils PUBLIC "external/SDL2_ttf-2.22.0/include")
target_include_directories(SDLUtils PUBLIC "external/SDL2_image-2.8.2/include")
target_link_libraries(SDLUtils PUBLIC ${SDLLibPath} ${SDL_IMGLibPath} ${SDL_TTFLibPath})
target_link_libraries(SDLUtils PUBLIC Utils)
set_property(TARGET SDLUtils PROPERTY CXX_STANDARD 20)

file(GLOB BangSources src/*.cc include/*.h)
add_executable(BangGame ${BangSources})
target_link_libraries(BangGame PUBLIC Bang Utils Graphics SDLUtils)
target_include_directories(BangGame PUBLIC "include/")
target_include_directories(BangGame PUBLIC "include/GraphicsLib")
set_property(TARGET BangGame PROPERTY CXX_STANDARD 20)
add_custom_command(
  TARGET BangGame POST_BUILD
  COMMAND for %I in ("$<SHELL_PATH:${CMAKE_SOURCE_DIR}/external/SDL2-2.30.3/lib/x64/SDL2.dll>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/external/SDL2_image-2.8.2/lib/x64/SDL2_image.dll>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/external/SDL2_ttf-2.22.0/lib/x64/SDL2_ttf.dll>") do copy /y %I $<SHELL_PATH:$<TARGET_FILE_DIR:BangGame>>
  VERBATIM)
add_custom_command(
  TARGET BangGame POST_BUILD
  COMMAND xcopy "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/assets>" "$<SHELL_PATH:${CMAKE_BINARY_DIR}>\\" /E /Y
  VERBATIM)

set_target_properties(Bang PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(Graphics PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(Utils PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(SDLUtils PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(BangGame PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
