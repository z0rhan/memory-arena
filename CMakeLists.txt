cmake_minimum_required(VERSION 3.31)
project(arena)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    arena.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
