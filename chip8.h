#pragma once
#include <cstdint>

class Chip8 {
    public:
        Chip8();
        uint8_t register_[16]{};
        uint8_t memory_[4096];
        uint16_t index_register{0};
        uint16_t program_counter{0};
        uint8_t stack_[16]{};
        uint8_t stack_pointer{0};
        uint8_t delay_timer{0};
        uint8_t sound_timer{};
        bool keys_[16]{};
        bool display_[64][32]{};
        uint16_t opcode{0};

        void LoadROM(const char* filename);
};
