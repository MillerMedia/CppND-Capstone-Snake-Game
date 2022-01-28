#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "renderer.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
}

/*
 * This function has been updated to prevent the user
 * from going backwards into its own body
 */
void Controller::HandleInput(bool &running, Snake &snake, std::vector<int>button_coordinates) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
      // Ensure that it's not a repeat key press since you would change direction the same way two times in a row
    } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
            if(snake.size == 1 || (snake.direction != Snake::Direction::kDown || snake.direction != Snake::Direction::kUp)) {
                ChangeDirection(snake, Snake::Direction::kUp,
                                Snake::Direction::kDown);
            }
          break;

        case SDLK_DOWN:
            if(snake.size == 1 || (snake.direction != Snake::Direction::kDown || snake.direction != Snake::Direction::kUp)) {
                ChangeDirection(snake, Snake::Direction::kDown,
                                Snake::Direction::kUp);
            }
          break;

        case SDLK_LEFT:
            if(snake.size == 1 || (snake.direction != Snake::Direction::kLeft || snake.direction != Snake::Direction::kRight)) {
                ChangeDirection(snake, Snake::Direction::kLeft,
                                Snake::Direction::kRight);
            }
          break;

        case SDLK_RIGHT:
            if(snake.size == 1 || (snake.direction != Snake::Direction::kLeft || snake.direction != Snake::Direction::kRight)) {
                ChangeDirection(snake, Snake::Direction::kRight,
                                Snake::Direction::kLeft);
            }
          break;
      }
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if(!snake.alive) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                // See if it is in the range of the button
                int button_x = button_coordinates[0];
                int button_y = button_coordinates[1];
                int button_w = button_coordinates[2];
                int button_h = button_coordinates[3];

                if(e.button.x > button_x && e.button.x < (button_x + button_w) && e.button.y > button_y && e.button.y < (button_y + button_h)){
                    // Restart game
                    snake.is_new = true;
                }
            }
        }
        break;
    }
  }
}