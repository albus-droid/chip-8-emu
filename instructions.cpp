#include "chip8.h"

void Chip8::OP_00E0() {
   memset(video, 0, sizeof(video))
}

void Chip8::OP_00EE() {
   pc = stack[--sp];
}

void Chip8::OP_1nnn() {
  uint16_t address = opcode_ & 0x0FFFu;
  pc = address;
}

void Chip8::OP_2nnn() {
  uint16_t address = opcode_ & 0x0FFFu;
  stack[sp++] = pc;
  pc = address;
}

void Chip8::OP_3xkk() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t kk = opcode_ & 0x00FFu;
  if (register_[x] == kk) {
    pc += 2;
  }
}

void Chip8::OP_4xkk() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t kk = opcode_ & 0x00FFu;
  if (register_[x] != kk) {
    pc += 2;
  }
}

void Chip8::OP_5xy0() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t y = (opcode_ & 0x00F0u) >> 4;
  if (register_[x] == register_[y]) {
    pc += 2;
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
      program_counter_ += 2;
  }
}

void Chip8::OP_Annn() {
  uint16_t address = opcode_ & 0x0FFFu;
  index_ = address;
}

void Chip8::OP_Bnnn() {
  uint16_t address = opcode_ & 0x0FFFu;
  program_counter_ = register_[0] + address;
}

void Chip8::OP_Cxkk() {
  uint8_t x = (opcode_ & 0x0F00u) >> 8;
  uint8_t kk = opcode_ & 0x00FFu;

  register_[x] = dist_(rng_) & kk;
}
