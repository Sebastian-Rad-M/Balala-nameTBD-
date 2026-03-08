cmake_minimum_required(VERSION 3.10)

project(Balala)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. THE MAGIC BULLET: Automatically find EVERY .cpp file in this folder
file(GLOB SOURCES "*.cpp")

# 5. Smash them all together into an executable named "game"
add_executable(game ${SOURCES})
if(MSVC)
    add_compile_options(/utf-8)
endif()