#include <iostream>
#include <cstdint>
#include <array>
#include <cstdlib> // for srand()
#include <ctime>   // for time()
#include <cstdio>  // for fstream
#include <fstream>

#include "chip8.h"


Chip8::Chip8() {};
Chip8::~Chip8() {};

std::array<std::uint8_t, 80> fontset =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, //0
    0x20, 0x60, 0x20, 0x20, 0x70, //1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
    0x90, 0x90, 0xF0, 0x10, 0x10, //4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
    0xF0, 0x10, 0x20, 0x40, 0x40, //7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
    0xF0, 0x90, 0xF0, 0x90, 0x90, //A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
    0xF0, 0x80, 0x80, 0x80, 0xF0, //C
    0xE0, 0x90, 0x90, 0x90, 0xE0, //D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
    0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

void Chip8::initialize(){

  // Seed rng
  srand( time( NULL ) );

  // Initialize registers and memory once

  pc = 0x200;  // Most Chip-8 programs start at location 0x200 (512)
  sp = 0;      // Reset stack Pointer
  I  = 0;      // Reset memory address register
  opcode = 0;  // Reset opcode

  // Clear the stack, keypads and V registers

  V = {};
  stack = {};
  key = {};

  // Clear memory

  memory = {};

  // Reseting timers

  delay_timer = 0;
  sound_timer = 0;

  // Clear the display

  gfx = {};

  // Load font set into memory [przypomnij sobie o wypełnianiu arraya z STL i popraw]

  for ( size_t i = 0; i < 80; i++ ) {
    memory[i] = fontset[i];
  }

}


void Chip8::loadGame(){

  initialize();

  const char* filename = "pong.rom";
  unsigned pos = 0x200;

  for( std::ifstream f(filename, std::ios::binary); f.good(); )
    memory[pos++ & 0xFFF] = f.get();
/*
  const int BUFFERSIZE = 2048;
  const char* fname = "pong.rom";
  FILE* filp = fopen(fname, "rb");

  if( !filp ){
    std::cout << "Error: couldn't open the file" << '\n';
  }

  char * buffer = new char [BUFFERSIZE];
  int bytes_read = fread(buffer, sizeof(char), BUFFERSIZE, filp);

  for ( size_t i = 0; i < bytes_read; i++ ) {
    memory[i + 512] = buffer[i];
  }

  fclose(filp);
  */

}


void Chip8::emulateOneCycle(){

  // Fetch Opcode [ the first fetching takes place at memory at 0x200 and 0x201 -- where the program data is starting ]

  opcode = memory[pc] << 8 | memory[pc+1];

  // Decode Opcode [ "wyciągamy" tutaj informację o tym jaki znak stoi na pierwszym miejscu danego opcodu - działa to dla większości opcodów,
  //                 ale dla niektórych będziemy musieli zrobić dodatkowe switche sprawdzające znaki na kolejnych miejscach ]

  switch ( opcode & 0xF000 ){

    case 0x0000:

      switch ( opcode & 0x000F ){

        case 0x0000:  //00E0
          gfx = {};
          drawFlag = true;
          pc += 2;
          break;

        case 0x000E:  //00EE
          sp--;
          pc = stack[sp];
          pc += 2;
          break;

        default:
          exit(3);
      }

    case 0x1000:  // 1nnn
      pc = opcode & 0x0FFF;
      break;

    case 0x2000:  // 2nnn
      stack[sp] = pc;
      sp++;
      pc = opcode & 0x0FFF;
      break;

    case 0x3000:  // 3xkk -- błąd w instrukcji, powinno być pc += 4
      if( V[( opcode & 0x0F00 ) >> 8] == opcode & 0x00FF )
        pc += 4;
      else
        pc += 2;
      break;

    case 0x4000:  // 4xkk
      if( V[( opcode & 0x0F00 ) >> 8] != opcode & 0x00FF )
        pc += 4;
      else
        pc += 2;
      break;

    case 0x5000:  // 5xy0
      if( V[( opcode & 0x0F00 ) >> 8] == V[(opcode & 0x00F0) >> 4] )
        pc += 4;
      else
        pc += 2;
      break;

    case 0x6000:  // 6xkk
      V[( opcode & 0x0F00 ) >> 8] = opcode & 0x00FF;
      pc += 2;
      break;

    case 0x7000:  // 7xkk
      V[( opcode & 0x0F00 ) >> 8] += opcode & 0x00FF;
      pc += 2;
      break;

    case 0x8000:

      switch( opcode & 0x000F ){

        case 0x0000:  // 8xy0
          V[( opcode & 0x0F00 ) >> 8] = V[( opcode & 0x00F0 ) >> 4];
          pc +=2;
          break;

        case 0x0001:  // 8xy1
          V[( opcode & 0x0F00 ) >> 8] |= V[( opcode & 0x00F0 ) >> 4];
          pc +=2;
          break;

        case 0x0002:  // 8xy2
          V[( opcode & 0x0F00 ) >> 8] &= V[( opcode & 0x00F0 ) >> 4];
          pc +=2;
          break;

        case 0x0003:  // 8xy3
          V[( opcode & 0x0F00 ) >> 8] ^= V[( opcode & 0x00F0 ) >> 4];
          pc +=2;
          break;

        case 0x0004:  // 8xy4
          if( V[( opcode & 0x00F0 ) >> 4] > ( 0xFF - V[opcode & 0x0F00] ) )
            V[0xF] = 1;
          else
            V[0xF] = 0;
          V[( opcode & 0x0F00 ) >> 8] += V[( opcode & 0x00F0 ) >> 4];
          pc += 2;
          break;

        case 0x0005:  // 8xy5
          if( V[( opcode & 0x0F00 ) >> 8] > V[( opcode & 0x00F0 ) >> 4] )
            V[0xF] = 1;
          else
            V[0xF] = 0;
          V[( opcode & 0x0F00 ) >> 8] -= V[( opcode & 0x00F0 ) >> 4];
          pc += 2;
          break;

        case 0x0006:  // 8xy6
                      // Store the value of register VY shifted right one bit in register VX
                      // Set register VF to the least significant bit prior to the shift
          V[0xF] = V[( opcode & 0x0F00 ) >> 8] & 0x1;  // zachowany ostatni bit V[x]!
          V[( opcode & 0x0F00 ) >> 8] = V[( opcode & 0x00F0 ) >> 4] >> 1;
          pc += 2;
          break;

        case 0x0007:  // 8xy7
          if( V[( opcode & 0x00F0 ) >> 4] > V[( opcode & 0x0F00 ) >> 8] )
            V[0xF] = 1;
          else
            V[0xF] = 0;
          V[( opcode & 0x0F00 ) >> 8] = V[( opcode & 0x00F0 ) >> 4] - V[( opcode & 0x0F00 ) >> 8];
          pc += 2;
          break;

        case 0x000E:  // 8xyE
                      // Store the value of register VY shifted left one bit in register VX
                      // Set register VF to the most significant bit prior to the shift
        V[0xF] = V[( opcode & 0x0F00 ) >> 8] >> 7;  // zachowany najważniejszy bit V[x]! (nie będzie zawsze zero?)
        V[( opcode & 0x0F00 ) >> 8] = V[( opcode & 0x00F0 ) >> 4] << 1;
        pc += 2;
        break;

        default:
        exit(4);
      }

    case 0x9000:  // 9xy0
      if( V[( opcode & 0x0F00 ) >> 8] != V[( opcode & 0x00F0 ) >> 4] )
        pc += 4;
      else
        pc += 2;
      break;

    case 0xA000:  // Annn
      I = opcode & 0x0FFF;
      pc += 2;
      break;

    case 0xB000:  // Bnnn
      pc = ( opcode & 0x0FFF ) + V[0];
      break;

    case 0xC000:  // Cxkk DO PRZEROBIENIA, DODAJ SRAND
      V[( opcode & 0x0F00 ) >> 8] = ( rand() % ( 0xFF + 1 ) ) & ( opcode & 0x00FF );
      pc += 2;
      break;

    case 0xD000:  // Dxyn SPRAWDŹ CZY TO OKEJ
    {
      std::uint16_t x = V[( opcode & 0x0F00 ) >> 8];
      std::uint16_t y = V[( opcode & 0x00F0 ) >> 4];
      std::uint16_t height = opcode & 0x000F;
      std::uint16_t pixel;

      V[0xF] = 0;
      for ( size_t yline = 0; yline < height; yline++ ) {
        pixel = memory[I + yline];
        for ( size_t xline = 0; xline < 8; xline++ ) {
          if ( ( pixel & ( 0x80 >> xline ) ) != 0 ) {
            if ( gfx[( x + xline + ((y + yline) *64 ) )] == 1 )
              V[0xF] = 1;
            gfx[x + xline + ( ( y + yline ) * 64 )] ^= 1;
          }
        }
      }
      drawFlag = true;
      pc += 2;
    }
    break;

    case 0xE000:
      switch( opcode & 0x000F ){

        case 0x000E:
          if ( key[V[( opcode & 0x0F00 ) >> 8]] != 0 )
            pc += 4;
          else
            pc += 2;
          break;

        case 0x0001:
          if ( key[V[( opcode & 0x0F00 ) >> 8]] == 0 )
            pc += 4;
          else
            pc += 2;
          break;

        default:
          exit( 5 );
      }

    case 0xF000:
      switch( opcode & 0x00FF ){

        case 0x0007:  // Fx07
          V[( opcode & 0x0F00 ) >> 8] = delay_timer;
          pc += 2;
          break;

        case 0x000A:  // Fx0A ??? skopiowane od kogoś
        {
          bool key_pressed = false;

          for ( size_t i = 0; i < 16; i++ ) {
            if( key[i] != 0 ){
              V[( opcode & 0x0F00 ) >> 8] = i;
              key_pressed = true;
            }
          }

          if( !key_pressed )
            return;

          pc += 2;
        }
        break;

        case 0x0015:  // Fx15
          delay_timer = V[( opcode & 0x0F00 ) >> 8];
          pc +=2 ;
          break;

        case 0x0018:  // Fx18
          sound_timer = V[( opcode & 0x0F00 ) >> 8];
          pc +=2 ;
          break;

        case 0x001E:  // Fx1E  [czy może tutaj dojść do range overflow jeśli I to zmienna 16 bitowa? chyba nie]
          I += V[( opcode & 0x0F00 ) >> 8];
          pc += 2;
          break;

        case 0x0029:  // Fx29  ??? skopiowane od kogoś
          I = V[( opcode & 0x0F00 ) >> 8] * 0x5;
          pc += 2;
          break;

        case 0x0033:  // Fx33
          memory[I]     =   V[( opcode & 0x0F00 ) >> 8] / 100;
          memory[I + 1] = ( V[( opcode & 0x0F00 ) >> 8] / 10) % 10;
          memory[I + 2] = ( V[( opcode & 0x0F00 ) >> 8] % 100) % 10;
          pc += 2;
          break;

        case 0x0055:  // Fx55
          for ( size_t i = 0; i <= V[( opcode & 0x0F00 ) >> 8]; i++ ) {
            memory[I + i] = V[i];
          }
          I += ( ( opcode & 0x0F00 ) >> 8 ) + 1;
          pc += 2;
          break;

        case 0x0065:  // Fx65
          for ( size_t i = 0; i <= V[( opcode & 0x0F00 ) >> 8]; i++ ) {
            V[i] = memory[I + i];
          }
          I += ( ( opcode & 0x0F00 ) >> 8 ) + 1;
          pc += 2;
          break;

        default:
          exit( 6 );
      }

      default:
        exit( 8 );

  }

  // Update timers
  if( delay_timer > 0 )
    delay_timer--;

  if( sound_timer > 0 )
    if( sound_timer == 1 )
      //DŹWIĘK
    sound_timer--;
}
