cmake_minimum_required(VERSION 3.11...4.3)
project(cppstl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main src/main.cpp)
add_executable(sandbox src/sandbox.cpp)

target_include_directories(main PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)