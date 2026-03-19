#include <chrono>
#include <iostream>

#include "chip8.h"
#include "window.h"

int main(int argc,char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 0;
    }

    char *rom_file = argv[1];

    Window window("Chip8", 640, 320, 64, 32);
    Chip8 chip8;

    chip8.LoadROM(rom_file);

    int video_pitch = sizeof(chip8.display_[0][0]) * 64;
    auto last_time = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit) {
        quit = window.ProcessInput(chip8.keys_);
        auto current_time = std::chrono::high_resolution_clock::now();
        float delta = std::chrono::duration<float, std::chrono::milliseconds::period>(current_time - last_time).count();
        if (delta >= 10 ) {
            last_time = current_time;
            chip8.Cycle();
            uint32_t pixels[32][64];
            for (int y = 0; y < 32; y++)
                for (int x = 0; x < 64; x++)
                    pixels[y][x] = chip8.display_[y][x] ? 0x00FF00FF : 0x00000000 ;
            window.UpdateWindow(pixels, sizeof(pixels[0][0]) * 64);
        }
    }
    return 0;
}
