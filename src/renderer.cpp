#include "renderer.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <sys/stat.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
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

  // Reference: https://stackoverflow.com/a/63003939/975592
  /*int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if((initted & flags) != flags) {
      printf("IMG_Init: Failed to init required jpg and png support!\n");
      printf("IMG_Init: %s\n", IMG_GetError());
  }*/

}

Renderer::~Renderer() {
    //TTF_Quit();
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

  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, transparency_level);

  // For debugging
  if(!snake.alive) {
      //DisplayResults(score);
      DisplayNewGameButton();
  }

  if(snake.alive){
      SDL_RenderFillRect(sdl_renderer, &block);
  }

  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

/*void Renderer::DisplayResults(int score){
    SDL_Rect rect;

    // The results screen will fill 50% of the screen
    rect.w = results_width;
    rect.h = results_height;
    rect.x = results_x;
    rect.y = results_y;

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(sdl_renderer, &rect);

    //DisplayScore(score, rect.x, rect.y, rect);
};*/

void Renderer::DisplayNewGameButton(){
    SDL_Rect button_image;
    button_image.w = 320;
    button_image.h = 106;
    button_image.x = static_cast<int>(results_width + results_x) - (results_width / 2) - (button_image.w / 2);
    button_image.y = static_cast<int>(results_height + results_y) - (button_image.h * 2);

    SDL_Surface *image_surface = nullptr;

    const char *filePath = "../src/new-game-button.png";
    struct stat fileInfo;
    assert(stat(filePath, &fileInfo) == 0 && "Texture file does not exist!");
    image_surface = IMG_Load(filePath);

    if(image_surface == nullptr)
    {
        std::cout << "Cannot find image.\n" << std::endl;
    }

    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(sdl_renderer, image_surface);
    SDL_FreeSurface(image_surface);

    SDL_RenderCopy(sdl_renderer, image_texture, nullptr, &button_image);

    SDL_DestroyTexture(image_texture);

    // Add to vector to be used in controller
    button_coordinates.emplace_back(button_image.x);
    button_coordinates.emplace_back(button_image.y);
    button_coordinates.emplace_back(button_image.w);
    button_coordinates.emplace_back(button_image.h);
};

/*void Renderer::DisplayScore(int score, int x, int y, SDL_Rect rect) {
    // Reference: https://stackoverflow.com/q/63000761/975592
    TTF_Init();
    default_font = TTF_OpenFont("../src/arial.ttf", 12);

    if(default_font == nullptr)
    {
        std::cout << "Font not created.\n" << std::endl;
        std::cout << TTF_GetError() << "\n" << std::endl;
    }

    std::string score_string = std::to_string(score);
    score_string += "Final string: ";
    char const *num_char = score_string.c_str();

    SDL_Surface *text_surface = nullptr;
    text_surface = TTF_RenderText_Solid(
            default_font,
            num_char,
            {0,0,0});

    if(text_surface == nullptr)
    {
        std::cout << "Text surface not created.\n" << std::endl;
        std::cout << TTF_GetError() << "\n" << std::endl;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
    SDL_FreeSurface(text_surface);

    SDL_Rect textrect;
    textrect.x = rect.x;
    textrect.y = rect.y;
    textrect.w = 100;
    textrect.h = 100;
    SDL_RenderCopy(sdl_renderer, text_texture, nullptr, &textrect);
    SDL_DestroyTexture(text_texture);
};*/
