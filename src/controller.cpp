#include "controller.h"
#include <iostream>
#include "SDL.h"

// void Controller::ChangeDirection(Tetromino &tetro) const {
//   if (snake.direction != opposite || snake.size == 1) snake.direction = input;
//   return;
// }

// void Controller::HandleInput(bool &running, TetrominoInstance &tetro) const {

// }

void Controller::HandleInput(bool &running, TetrominoInstance &tetro) const
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                break;

            case SDLK_DOWN:
                break;

            case SDLK_LEFT:
                break;

            case SDLK_RIGHT:
                break;
            }
        }
    }
}