cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Minesweeper)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)
add_executable(Minesweeper SMFL_Practice_1.cpp main.cpp NumClass.cpp NumClass.h Tile.cpp Tile.h TextureManager.cpp TextureManager.h Random.cpp Random.h Board.h Face.h)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)
