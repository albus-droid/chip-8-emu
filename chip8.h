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
        uint16_t opcode_{0};

        void LoadROM(const char* filename);
        void Cycle();

        void OP_00E0();
        void OP_00EE();
        void OP_1nnn();
        void OP_2nnn();
        void OP_3xkk();
        void OP_4xkk();
        void OP_5xy0();
        void OP_6xkk();
        void OP_7xkk();
        void OP_8xy0();
        void OP_8xy1();
        void OP_8xy2();
        void OP_8xy3();
        void OP_8xy4();
        void OP_8xy5();
        void OP_8xy6();
        void OP_8xy7();
        void OP_8xyE();
        void OP_9xy0();
        void OP_Annn();
        void OP_Bnnn();
        void OP_Cxkk();
        void OP_Dxyn();
        void OP_Ex9E();
        void OP_ExA1();
        void OP_Fx07();
        void OP_Fx0A();
        void OP_Fx15();
        void OP_Fx18();
        void OP_Fx1E();
        void OP_Fx29();
        void OP_Fx33();
        void OP_Fx55();
        void OP_Fx65();
};
