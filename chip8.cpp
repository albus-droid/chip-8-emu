#include "chip8.h"
#include <iostream>
#include <fstream>

const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8() {
    program_counter = START_ADDRESS;
    std::cout << "Chip8 initialized. PC = 0x" << std::hex << program_counter << std::endl;
}

void Chip8::LoadROM(const char* filename) {
    std::ifstream rom_file(filename, std::ios::binary | std::ios::ate);
    if (!rom_file.is_open()) {
        std::cerr << "Failed to open ROM file: " << filename << std::endl;
        return;
    }

    std::streampos rom_size = rom_file.tellg();
    rom_file.seekg(0, std::ios::beg);

    char *buffer = new char[rom_size];
    rom_file.read(buffer, rom_size);
    rom_file.close();

    for (size_t i = 0; i < rom_size; ++i) {
        memory_[START_ADDRESS + i] = buffer[i];
    }

    delete[] buffer;

    std::cout << "Loaded ROM: " << filename << " (" << rom_size << " bytes)" << std::endl;
}
