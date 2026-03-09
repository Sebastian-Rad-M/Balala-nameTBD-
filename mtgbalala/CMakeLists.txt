cmake_minimum_required(VERSION 3.10)

project(Balala)
set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "*.cpp")

add_executable(game ${SOURCES})
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system)

if(MSVC)
	add_compile_options(/utf-8)
endif()
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
