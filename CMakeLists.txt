cmake_minimum_required(VERSION 3.14)
project(chip8)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(chip8
    src/main.cpp
    src/chip8.cpp
    src/opcode-table.cpp
    src/instructions.cpp
    src/window.cpp
)

target_include_directories(chip8 PRIVATE src ${SDL2_INCLUDE_DIRS})
target_link_libraries(chip8 PRIVATE ${SDL2_LIBRARIES})
target_compile_options(chip8 PRIVATE -Wall -Wextra -Wpedantic -Werror)
