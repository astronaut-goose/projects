#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <cstdint>

class Chip8
{

private:
  std::array<std::uint8_t, 16> V;        // 16 8-bit general purpose registers (V0-VF)
  std::uint16_t I;                       // 16-bit register for storing memory address

  std::uint8_t delay_timer;              // The delay timer is active whenever the delay timer register (DT) is non-zero
  std::uint8_t sound_timer;              // The sound timer is active whenever the sound timer register (ST) is non-zero

  std::uint16_t pc;                      // Program Counter (PC) is used to store the currently executing address
  std::uint8_t sp;                       // Stack Pointer (SP) is used to point to the topmost level of the stack

  std::array<std::uint16_t, 16> stack;   // Stack used to store the address that the interpreter should return to when finished with a subroutine
  std::array<std::uint8_t, 4096> memory; // The Chip-8 language is capable of accessing up to 4KB (4,096 bytes) of RAM, from location 0x000 (0) to 0xFFF (4095)

  std::uint16_t opcode;                  // Stores the current opcode

public:
  Chip8();
  ~Chip8();

  void emulateOneCycle();
  void initialize();
  void loadGame();

  bool drawFlag;

  std::array<std::uint8_t, 64*32> gfx;   // The graphics of the Chip8 are black and white and the screen has a total of 2048 pixels (64 x 32)
  std::array<std::uint8_t, 16> key;      // Indicates the current state of keys

};


#endif // CHIP8_H
