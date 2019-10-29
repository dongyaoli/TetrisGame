#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, Tetromino &tetro) const
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
                tetro.MoveLeft();
                break;
            case SDLK_RIGHT:
                tetro.MoveRight();
                break;
            case SDLK_m:
                tetro.TurnLeft();
                break;
            case SDLK_n:
                tetro.TurnRight();
                break;
            }
        }
    }
}