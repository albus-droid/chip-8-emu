#include "chip8.h"
#include "fontset.h"

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8()
    : rng_(std::chrono::system_clock::now().time_since_epoch().count())
{
    program_counter = START_ADDRESS;

    //RNG
    dist_ = std::uniform_int_distribution<uint8_t>(0, 255U);

    for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory_[FONTSET_START_ADDRESS + i] = fontset[i];
    }

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

void Chip8::Cycle() {
    opcode_ = (memory_[program_counter] << 8u) | memory_[program_counter + 1];
    program_counter += 2;

    std::cout << "Opcode: 0x" << std::hex << std::uppercase << opcode_ << std::endl;
}
