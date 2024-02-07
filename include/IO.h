#pragma once

#include "types.h"
#include "SDL2/SDL.h"

class IO {
public:

  IO(char const* title, int win_width, int win_height, int texture_width, int texture_height);

  ~IO();

  void update(void const* buffer, int pitch);

  bool process_input(byte* keys);

private:
  
  SDL_Window* window{};
  SDL_Renderer* renderer{};
  SDL_Texture* texture{};
};
