#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "tetro.h"

class Controller
{
public:
    void HandleInput(bool &running, Tetromino &tetro) const;

private:
};

#endif // CONTROLLER_H