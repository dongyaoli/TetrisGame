#ifndef CONTROLLER_H
#define CONTROLLER_H

// #include "tetromino.h"
#include "tetro.h"

class Controller
{
public:
    void HandleInput(bool &running, Tetromino &tetro) const;

private:
    // void ChangeDirection(Snake &snake, Snake::Direction input,
    //                      Snake::Direction opposite) const;
};

#endif // CONTROLLER_H