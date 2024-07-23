cmake_minimum_required(VERSION 3.27)
project(Bang)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(jsoncpp_DIR "${CMAKE_SOURCE_DIR}/vendor/jsoncpp/lib/cmake/jsoncpp")
find_package(jsoncpp 1.9.5 REQUIRED)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2/cmake")
find_package(SDL2 2.31.0 REQUIRED)

set(SDL2_image_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_image/cmake")
find_package(SDL2_image 2.9.0 REQUIRED)

set(SDL2_ttf_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_ttf/cmake")
find_package(SDL2_ttf 2.23.0 REQUIRED)

file(GLOB BangLibSources src/BangLib/*.cc include/BangLib/*.h)
add_library(Bang STATIC ${BangLibSources})
target_include_directories(Bang PUBLIC "include/BangLib")
target_include_directories(Bang PUBLIC "include/UtilsLib")
target_include_directories(Bang PUBLIC "include/SDLUtilsLib")
target_include_directories(Bang PUBLIC "vendor/jsoncpp/include")
target_include_directories(Bang PUBLIC "vendor/SDL2/include/SDL2")
target_include_directories(Bang PUBLIC "vendor/SDL2_image/include/SDL2")
target_include_directories(Bang PUBLIC "vendor/SDL2_ttf/include/SDL2")
set_property(TARGET Bang PROPERTY CXX_STANDARD 20)

file(GLOB UtilsLibSources src/UtilsLib/*.cc include/UtilsLib/*.h)
add_library(Utils SHARED ${UtilsLibSources})
target_include_directories(Utils PUBLIC "include/UtilsLib")
target_include_directories(Utils PUBLIC "vendor/SDL2/include/SDL2")
target_include_directories(Utils PUBLIC "vendor/SDL2_image/include/SDL2")
target_include_directories(Utils PUBLIC "vendor/SDL2_ttf/include/SDL2")
target_include_directories(Utils PUBLIC "vendor/jsoncpp/include")
target_link_libraries(Utils PUBLIC JsonCpp::JsonCpp)
set_property(TARGET Utils PROPERTY CXX_STANDARD 20)

file(GLOB GraphicsLibSources src/GraphicsLib/*.cc include/GraphicsLib/*.h)
add_library(Graphics SHARED ${GraphicsLibSources})
target_include_directories(Graphics PUBLIC "include/GraphicsLib")
target_include_directories(Graphics PUBLIC "include/UtilsLib")
target_include_directories(Graphics PUBLIC "include/SDLUtilsLib")
target_include_directories(Graphics PUBLIC "vendor/SDL2/include/SDL2")
target_link_libraries(Graphics PUBLIC Utils)
set_property(TARGET Graphics PROPERTY CXX_STANDARD 20)

file(GLOB SDLUtilsLibSources src/SDLUtilsLib/*.cc include/SDLUtilsLib/*.h)
add_library(SDLUtils SHARED ${SDLUtilsLibSources})
target_include_directories(SDLUtils PUBLIC "include/SDLUtilsLib")
target_include_directories(SDLUtils PUBLIC "include/UtilsLib")
target_include_directories(SDLUtils PUBLIC "vendor/SDL2/include/SDL2")
target_include_directories(SDLUtils PUBLIC "vendor/SDL2_ttf/include/SDL2")
target_include_directories(SDLUtils PUBLIC "vendor/SDL2_image/include/SDL2")
target_link_libraries(SDLUtils PUBLIC SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
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
  COMMAND for %I in ("$<SHELL_PATH:${CMAKE_SOURCE_DIR}/vendor/jsoncpp/bin/jsoncpp.dll>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/vendor/SDL2/bin/SDL2.dll>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/vendor/SDL2_image/bin/SDL2_image.dll>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/vendor/SDL2_ttf/bin//SDL2_ttf.dll>") do copy /y %I $<SHELL_PATH:$<TARGET_FILE_DIR:BangGame>>
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

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BangGame)
