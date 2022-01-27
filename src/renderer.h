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
    void DisplayNewGameButton();
    void DisplayText(const char *message, int x, int y, SDL_Rect rect);

    int results_width;
    int results_height;
    int results_x;
    int results_y;

    SDL_Rect button_image;

 private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;

    TTF_Font * default_font;
};

#endif