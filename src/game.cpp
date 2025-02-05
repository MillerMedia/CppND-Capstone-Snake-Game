#include "game.h"
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
#include "audio.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
    RandomPlacement("food");

  initAudio();
  food_sound = createAudio("../src/smb_coin.wav", 0, SDL_MIX_MAXVOLUME / 2);
  end_music = createAudio("../src/smb_gameover.wav", 0, SDL_MIX_MAXVOLUME / 2);
  Start();
}

// Run this at the beginning of every iteration of the game
void Game::Start(){
    play_end_song = true;
    snake.alive = true;
    snake.size = 1;
    snake.speed = 0.1f;
    snake.body = {};
    score = 0;
    RandomPlacement("snake");
    RandomPlacement("food");
    snake.is_new = false;
};

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (running) {
      if(snake.is_new){
          Start();
      }

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, renderer.button_coordinates);
    Update();
    renderer.Render(snake, food, score);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::RandomPlacement(std::string item_type) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if(item_type == "food") {
        if (!snake.SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    } else if(item_type == "snake") {
        snake.head_x = x;
        snake.head_y = y;
        return;
    }

    return;
  }
}

void Game::Update() {
  if (!snake.alive) {
      if(play_end_song) {
          playSoundFromMemory(end_music, SDL_MIX_MAXVOLUME / 2);
          play_end_song = false;
      }

      return;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
      RandomPlacement("food");

    // Need to play it in its own thread
    playSoundFromMemory(food_sound, SDL_MIX_MAXVOLUME / 2);

    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }