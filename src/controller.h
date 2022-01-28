#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, std::vector<int>button_coordinates) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

  // Reference: https://stackoverflow.com/a/35165854/975592
  //void MousePress(SDL_MouseButtonEvent &b, Snake &snake, std::vector<int>button_coordinates);
};

#endif