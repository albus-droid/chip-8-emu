#include "chip8.h"
#include "fontset.h"
#include <cstdint>

void Chip8::OP_00E0() {
   memset(display_, 0, sizeof(display_));
}

void Chip8::OP_00EE() {
   program_counter = stack_[--stack_pointer];
}

void Chip8::OP_1nnn() {
  uint16_t address = opcode_ & 0x0FFFu;
  program_counter = address;
}

void Chip8::OP_2nnn() {
  uint16_t address = opcode_ & 0x0FFFu;
  stack_[stack_pointer++] = program_counter;
  program_counter = address;
}

void Chip8::OP_3xkk() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t kk = opcode_ & 0x00FFu;
  if (register_[x] == kk) {
    program_counter += 2;
  }
}

void Chip8::OP_4xkk() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t kk = opcode_ & 0x00FFu;
  if (register_[x] != kk) {
    program_counter += 2;
  }
}

void Chip8::OP_5xy0() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;
  if (register_[x] == register_[y]) {
    program_counter += 2;
  }
}

void Chip8::OP_6xkk() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t kk = opcode_ & 0x00FFu;
  register_[x] = kk;
}

void Chip8::OP_7xkk() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;
    uint8_t kk = opcode_ & 0x00FFu;
    register_[x] += kk;
}

void Chip8::OP_8xy0() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;
  register_[x] = register_[y];
}

void Chip8::OP_8xy1() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;
  register_[x] |= register_[y];
}

void Chip8::OP_8xy2() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;
  register_[x] &= register_[y];
}

void Chip8::OP_8xy3() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;
  register_[x] ^= register_[y];
}

void Chip8::OP_8xy4() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;

  uint16_t sum = register_[x] + register_[y];

  if (sum > 255u) {
    register_[0xF] = 1u;
  } else {
    register_[0xF] = 0u;
  }
  register_[x] = sum & 0xFFu;
}

void Chip8::OP_8xy5() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;

  if (register_[x] > register_[y]) {
    register_[0xF] = 1u;
  } else {
    register_[0xF] = 0u;
  }
  register_[x] -= register_[y];
}

void Chip8::OP_8xy6() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;

  register_[0xF] = (register_[x] & 0x01u);
  register_[x] >>= 1;
}

void Chip8::OP_8xy7() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;

  if (register_[y] > register_[x]) {
    register_[0xF] = 1u;
  } else {
    register_[0xF] = 0u;
  }

  register_[x] = register_[y] - register_[x];
}

void Chip8::OP_8xyE() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;

  register_[0xF] = (register_[x] & 0x01u) >> 0;
  register_[x] <<= 1;
}

void Chip8::OP_9xy0() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;

  if (register_[x] != register_[y]) {
      program_counter += 2;
  }
}

void Chip8::OP_Annn() {
  uint16_t address = opcode_ & 0x0FFFu;
  index_register = address;
}

void Chip8::OP_Bnnn() {
  uint16_t address = opcode_ & 0x0FFFu;
  program_counter = register_[0] + address;
}

void Chip8::OP_Cxkk() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t kk = opcode_ & 0x00FFu;

  register_[x] = dist_(rng_) & kk;
}

void Chip8::OP_Dxyn() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;
  uint8_t h = opcode_ & 0x000Fu;

  uint8_t wrap_x = register_[x] % DISPLAY_WIDTH;
  uint8_t wrap_y = register_[y] % DISPLAY_HEIGHT;

  register_[0xF] = 0;

  for (uint8_t i = 0; i < h; ++i) {
    uint8_t sprite = memory_[index_register + i];
    for (uint8_t j = 0; j < 8; ++j) {
        uint8_t sprite_pixel = sprite & (0x80u >> j);
        bool* screen_pixel = &display_[wrap_y + i][wrap_x + j];
        if (sprite_pixel) {
            if (*screen_pixel == true) {
                register_[0xF] = 1;
            }
            *screen_pixel ^= true;
        }
    }
  }
}

void Chip8::OP_Ex9E() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t key = register_[x];

  if (keys_[key]) {
      program_counter += 2;
  }
}

void Chip8::OP_ExA1() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t key = register_[x];

  if (!keys_[key]) {
      program_counter += 2;
  }
}

void Chip8::OP_Fx07() {
    uint8_t x = (opcode_ & 0x0F00u);
    register_[x] = delay_timer;
}

void Chip8::OP_Fx0A() {
    uint8_t x = (opcode_ & 0x0F00u);
    for (uint8_t i = 0; i < 16; ++i) {
        if (keys_[i]) {
            register_[x] = i;
            return;
        }
    }
    program_counter -= 2;
}

void Chip8::OP_Fx15() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;
    delay_timer = register_[x];
}

void Chip8::OP_Fx18() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;
    sound_timer = register_[x];
}

void Chip8::OP_Fx1E() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;
    index_register += register_[x];
}

void Chip8::OP_Fx29() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;
    uint8_t digit = register_[x];
    index_register = FONTSET_START_ADDRESS + digit * 5;
}

void Chip8::OP_Fx33() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;
    uint8_t value = register_[x];

    memory_[index_register + 2] = value % 10;
    memory_[index_register + 1] = (value / 10) % 10;
    memory_[index_register] = (value / 100) % 10;
}

void Chip8::OP_Fx55() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;

    for (uint8_t i = 0; i <= x; ++i) {
        memory_[i + index_register] = register_[i];
    }
}

void Chip8::OP_Fx65() {
    uint8_t x = (opcode_ & 0x0F00u) >> 8;

    for (uint8_t i = 0; i <= x; ++i) {
        register_[i] = memory_[i + index_register];
    }
}
