#include "chip8.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: chip8-emu <rom_file>" << std::endl;
        return 1;
    }

    Chip8 chip8;
    chip8.LoadROM(argv[1]);

    std::cout << "First 20 bytes from 0x200:" << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << std::hex << (int)(chip8.memory_[i + 0x200]) << " ";
    }
    std::cout << std::endl;
    return 0;
}
