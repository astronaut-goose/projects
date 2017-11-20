#include <iostream>
#include <cstdint>

#include <chrono>
#include <thread>

#include "SDL2/SDL.h"

#include "chip8.h"


// Keypad keymap
uint8_t keymap[16] = {
    SDLK_x,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_q,
    SDLK_w,
    SDLK_e,
    SDLK_a,
    SDLK_s,
    SDLK_d,
    SDLK_z,
    SDLK_c,
    SDLK_4,
    SDLK_r,
    SDLK_f,
    SDLK_v,
};

int main(int argc, char** argv)
{
  Chip8 chip8;

//Screen dimension constants
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 512;

  //The window we'll be rendering to
  SDL_Window* window = NULL;

  // Initialize SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
  }

  // Create window
  window = SDL_CreateWindow( "CHIP-8 EMULATOR",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH,
                             SCREEN_HEIGHT,
                             SDL_WINDOW_SHOWN );
  if( window == NULL ){
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
  }

  // Create renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

  // Create texture that stores frame buffer
  SDL_Texture* sdlTexture = SDL_CreateTexture(renderer,
          SDL_PIXELFORMAT_ARGB8888,
          SDL_TEXTUREACCESS_STREAMING,
          64, 32);

  // Temporary pixel buffer
  uint32_t pixels[2048];

  // Initialize the Chip8 system and load the game into the memory
  //chip8.initialize();

  // Load ROM
  chip8.loadGame();

  //Emulation loop
  while( true ){
    chip8.emulateOneCycle();

    // Process SDL events
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) exit(0);

        // Process keydown events
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                exit(0);

            //if (e.key.keysym.sym == SDLK_F1)
            //    goto load;      // *gasp*, a goto statement!
                                // Used to reset/reload ROM

            for (int i = 0; i < 16; ++i) {
                if (e.key.keysym.sym == keymap[i]) {
                    chip8.key[i] = 1;
                }
            }
        }
        // Process keyup events
        if (e.type == SDL_KEYUP) {
            for (int i = 0; i < 16; ++i) {
                if (e.key.keysym.sym == keymap[i]) {
                    chip8.key[i] = 0;
                }
            }
        }
    }

    // If draw occurred, redraw SDL screen
    if (chip8.drawFlag) {
        chip8.drawFlag = false;

        // Store pixels in temporary buffer
        for (int i = 0; i < 2048; ++i) {
            uint8_t pixel = chip8.gfx[i];
            pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
        }
        // Update SDL texture
        SDL_UpdateTexture(sdlTexture, NULL, pixels, 64 * sizeof(Uint32));
        // Clear screen and render
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    // Sleep to slow down emulation speed
    std::this_thread::sleep_for(std::chrono::microseconds(1200));

  }

  return 0;
}
