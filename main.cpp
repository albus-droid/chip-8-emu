#include "chip8.h"
#include "fontset.h"

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

    std::cout << "Fontset loaded:" << std::endl;

    const char* labels = "0123456789ABCDEF";

    for (unsigned int i = 0; i < 16; i++) {
        std::cout << labels[i] << ":\n";
        for (int row = 0; row < 5; row++) {
            uint8_t byte = chip8.memory_[FONTSET_START_ADDRESS + i * 5 + row];
            for (int bit = 7; bit >= 0; bit--) {
                std::cout << ((byte >> bit) & 1 ? "█" : " ");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
