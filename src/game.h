#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "audio.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void Start();
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  Audio * food_sound;
  Audio * end_music;
  bool play_end_song;
  bool running{true};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void RandomPlacement(std::string item_type);
  void Update();
};

#endif