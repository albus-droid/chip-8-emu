#include "chip8.h"
#include <iostream>

const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8() {
    program_counter = START_ADDRESS;
    std::cout << "Chip8 initialized. PC = 0x" << std::hex << program_counter << std::endl;
}
