#include "renderer.h"
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "audio.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      results_width(screen_width * 0.75),
      results_height(screen_height * 0.75),
      results_x((screen_width / 2) - (results_width / 2)),
      results_y((screen_height / 2) - (results_height / 2))
      {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(SDL_INIT_AUDIO) < 0 ) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
      std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initiate font
  //Initialize SDL_ttf
  if( TTF_Init() == -1 )
  {
      std::cerr << "SDL TTF could not be loading.\n";
  }
  default_font = TTF_OpenFont("arial.ttf", 25);

}

Renderer::~Renderer() {
    TTF_Quit();
    endAudio();
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, int score) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;
    auto transparency_level = SDL_ALPHA_OPAQUE;

    if(!snake.alive){
      transparency_level = SDL_ALPHA_TRANSPARENT;
    }

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, transparency_level);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;

  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, transparency_level);

  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;

  // For debugging
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, transparency_level);

  if(!snake.alive) {
      DisplayResults(score);
  }

  if(snake.alive){
      SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::DisplayResults(int score){
    SDL_Rect rect;

    // The results screen will fill 50% of the screen
    rect.w = static_cast<int>(results_width);
    rect.h = static_cast<int>(results_height);
    rect.x = static_cast<int>(results_x);
    rect.y = static_cast<int>(results_y);

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(sdl_renderer, &rect);

    DisplayNewGameButton("New Game");
    DisplayText("Your score:", 0, 0);
};

void Renderer::DisplayNewGameButton(const std::string message){
    SDL_Rect rect;

    rect.w = static_cast<int>(results_width / 3);
    rect.h = static_cast<int>(rect.w / 3);

    // Center horizontally
    rect.x = static_cast<int>(results_width + results_x) - (results_width / 2) - (rect.w / 2);
    rect.y = static_cast<int>(results_height + results_y) - (rect.h * 2);

    SDL_SetRenderDrawColor(sdl_renderer, 206, 206, 206, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(sdl_renderer, &rect);
};

void Renderer::DisplayText(const char *message, int x, int y) {
    // Reference: https://gigi.nullneuron.net/gigilabs/displaying-text-in-sdl2-with-sdl_ttf/
    SDL_Color color = { 125, 125, 125 };
    SDL_Surface * surface = TTF_RenderText_Solid(default_font, "Test Text.", color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);

    int texW = 100;
    int texH = 100;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { x, y, texW, texH };

    SDL_RenderCopy(sdl_renderer, texture, NULL, &dstrect);
    //SDL_RenderPresent(sdl_renderer);

    // Release resources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
};
