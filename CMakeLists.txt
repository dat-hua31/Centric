cmake_minimum_required(VERSION 3.15)

project(Centric LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 6.0
)
FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(Centric ${SOURCES})

target_include_directories(Centric PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(Centric PRIVATE raylib)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(Centric PRIVATE stdc++exp)
endif()