#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, int score);
  void UpdateWindowTitle(int score, int fps);

  void DisplayResults(int score);
  void DisplayNewGameButton(const std::string message);
  void DisplayText(const char *message, int x, int y);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  const std::size_t results_width;
  const std::size_t results_height;
  const std::size_t results_x;
  const std::size_t results_y;

  TTF_Font * default_font;
};

#endif