cmake_minimum_required(VERSION 3.27)
project(Bang)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
option(BANG_VENDORED "Use the dependencies in external, or try and find system-wide installed ones.")
option(BANG_JSONCPP_VENDORED "Since there might be problems with using preinstalled jsoncpp we can force using the included jsoncpp with this.")

set(JSONCPP_VERSION)
set(SDL2_VERSION)
set(SDL2IMAGE_VERSION)
set(SDL2TTF_VERSION)
set(CROSSGUID_VERSION)
set(JSONCPP_INCLUDE_DIR /usr/include)
if(${BANG_JSONCPP_VENDORED})
  set(JSONCPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/jsoncpp/include")
  set(jsoncpp_DIR "${CMAKE_SOURCE_DIR}/vendor/jsoncpp/lib/cmake/jsoncpp")
endif()
set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2IMAGE_INCLUDE_DIR /usr/include/SDL2)
set(SDL2TTF_INCLUDE_DIR /usr/include/SDL2)
if(${BANG_VENDORED})
  set(jsoncpp_DIR "${CMAKE_SOURCE_DIR}/vendor/jsoncpp/lib/cmake/jsoncpp")
  set(JSONCPP_VERSION 1.9.5)
  set(JSONCPP_INCLUDE_DIR vendor/jsoncpp/include/)
  set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2/cmake/")
  set(SDL2_VERSION 2.31.0)
  set(SDL2_INCLUDE_DIR vendor/SDL2/include/SDL2)
  set(SDL2_image_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_image/cmake/")
  set(SDL2IMAGE_VERSION 2.9.0)
  set(SDL2_INCLUDE_DIR vendor/SDL2_image/include/SDL2)
  set(SDL2_ttf_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_ttf/cmake/")
  set(SDL2TTF_VERSION 2.23.0)
  set(SDL2TTF_INCLUDE_DIR vendor/SDL2_ttf/include/SDL2)
  set(crossguid_DIR "${CMAKE_SOURCE_DIR}/vendor/crossguid/share/crossguid/cmake/")
  set(CROSSGUID_VERSION 0.2.3)
  set(CROSSGUID_INCLUDE_DIR vendor/crossguid/include/crossguid)
endif()
message(STATUS "jsoncpp_DIR: ${jsoncpp_DIR}")
message(STATUS "crossguid_DIR: ${crossguid_DIR}")

# Function to capture new imported targets created by find_package
function(collect_imported_dll_targets out_var)
  get_directory_property(all_targets IMPORTED_TARGETS)

  set(dll_targets)
  foreach(target IN LISTS all_targets)
    get_target_property(target_type ${target} TYPE)
    # Only capture SHARED or UNKNOWN (prebuilt imported) libraries
    if(target_type STREQUAL "SHARED_LIBRARY" OR target_type STREQUAL "UNKNOWN_LIBRARY")
      list(APPEND dll_targets ${target})
    endif()
  endforeach()

  set(${out_var} ${dll_targets} PARENT_SCOPE)
endfunction()

find_package(jsoncpp ${JSONCPP_VERSION} REQUIRED)
find_package(SDL2 ${SDL2_VERSION} REQUIRED)
find_package(SDL2_image ${SDL2IMAGE_VERSION} REQUIRED)
find_package(SDL2_ttf ${SDL2TTF_VERSION} REQUIRED)
find_package(crossguid REQUIRED)

collect_imported_dll_targets(3RD_PARTY_IMPORTED_TARGETS)

file(GLOB BangLibSources src/BangLib/*.cc include/BangLib/*.h include/BangLib/*.inc)
add_library(Bang STATIC ${BangLibSources})
target_include_directories(Bang PUBLIC "include/BangLib")
target_include_directories(Bang PUBLIC "include/GraphicsLib")
target_include_directories(Bang PUBLIC "include/UtilsLib")
target_include_directories(Bang PUBLIC "include/SDLUtilsLib")
target_include_directories(Bang PUBLIC ${JSONCPP_INCLUDE_DIR})
target_include_directories(Bang PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(Bang PUBLIC ${SDL2IMAGE_INCLUDE_DIR})
target_include_directories(Bang PUBLIC ${SDL2TTF_INCLUDE_DIR})
target_include_directories(Bang PUBLIC ${CROSSGUID_INCLUDE_DIR})
target_link_libraries(Bang PUBLIC JsonCpp::JsonCpp)
target_link_libraries(Bang PUBLIC crossguid)
set_property(TARGET Bang PROPERTY CXX_STANDARD 20)

file(GLOB UtilsLibSources src/UtilsLib/*.cc include/UtilsLib/*.h)
add_library(Utils SHARED ${UtilsLibSources})
target_include_directories(Utils PUBLIC "include/UtilsLib")
target_include_directories(Utils PUBLIC ${JSONCPP_INCLUDE_DIR})
target_include_directories(Utils PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(Utils PUBLIC ${SDL2IMAGE_INCLUDE_DIR})
target_include_directories(Utils PUBLIC ${SDL2TTF_INCLUDE_DIR})
target_include_directories(Utils PUBLIC ${CROSSGUID_INCLUDE_DIR})
target_link_libraries(Utils PUBLIC JsonCpp::JsonCpp)
target_link_libraries(Utils PUBLIC crossguid)
set_property(TARGET Utils PROPERTY CXX_STANDARD 20)

file(GLOB GraphicsLibSources src/GraphicsLib/*.cc include/GraphicsLib/*.h)
add_library(Graphics SHARED ${GraphicsLibSources})
target_include_directories(Graphics PUBLIC "include/GraphicsLib")
target_include_directories(Graphics PUBLIC "include/UtilsLib")
target_include_directories(Graphics PUBLIC "include/SDLUtilsLib")
target_include_directories(Graphics PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(Graphics PUBLIC Utils)
set_property(TARGET Graphics PROPERTY CXX_STANDARD 20)

file(GLOB SDLUtilsLibSources src/SDLUtilsLib/*.cc include/SDLUtilsLib/*.h)
add_library(SDLUtils SHARED ${SDLUtilsLibSources})
target_include_directories(SDLUtils PUBLIC "include/SDLUtilsLib")
target_include_directories(SDLUtils PUBLIC "include/UtilsLib")
target_include_directories(Bang PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(Bang PUBLIC ${SDL2IMAGE_INCLUDE_DIR})
target_include_directories(Bang PUBLIC ${SDL2TTF_INCLUDE_DIR})
target_link_libraries(SDLUtils PUBLIC SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
target_link_libraries(SDLUtils PUBLIC Utils)
set_property(TARGET SDLUtils PROPERTY CXX_STANDARD 20)

file(GLOB BangSources src/*.cc include/*.h)
add_executable(BangGame ${BangSources})
target_link_libraries(BangGame PUBLIC Bang Utils Graphics SDLUtils JsonCpp::JsonCpp)
target_include_directories(BangGame PUBLIC "include/")
target_include_directories(BangGame PUBLIC "include/GraphicsLib")
set_property(TARGET BangGame PROPERTY CXX_STANDARD 20)

if(WIN32)
  set(COPY_COMMANDS)

  foreach(target IN LISTS 3RD_PARTY_IMPORTED_TARGETS)
    if(TARGET ${target})
      # Check target type to prevent errors on INTERFACE or STATIC libraries
      get_target_property(target_type ${target} TYPE)

      if(target_type STREQUAL "SHARED_LIBRARY" OR target_type STREQUAL "UNKNOWN_LIBRARY")
        list(APPEND COPY_COMMANDS
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${target}>
            $<TARGET_FILE_DIR:BangGame>
        )
      endif()
    endif()
  endforeach()

  if(COPY_COMMANDS)
    add_custom_command(TARGET BangGame POST_BUILD
      ${COPY_COMMANDS}
      COMMENT "Copying shared library dependencies..."
      VERBATIM
    )
  endif()
endif()

add_custom_command(
  TARGET BangGame POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/assets>" "$<SHELL_PATH:${CMAKE_BINARY_DIR}/>"
  VERBATIM)

set_target_properties(Bang PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(Graphics PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(Utils PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(SDLUtils PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")
set_target_properties(BangGame PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" LIBRARY_OUTPUT_DIRECTORY "lib" RUNTIME_OUTPUT_DIRECTORY "bin")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BangGame)
