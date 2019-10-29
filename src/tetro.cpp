#include "tetro.h"

Tetromino::Tetromino(int tetroType, int rotation, float x, float y, int xLim)
{
    _tetroType = tetroType % numTetroTypes;
    _rotation = rotation % 4;
    _x = x;
    _y = y;
    _xLim = xLim;
};

void Tetromino::SetType(int newType)
{
    _tetroType = newType % numTetroTypes;
}

void Tetromino::SetRotation(int newRotation)
{
    _rotation = newRotation % 4;
}

void Tetromino::SetXLim(int xLim)
{
    if (xLim < 0) {_xLim = 0;}
    else {_xLim = xLim;}
}

int Tetromino::GetTetroType() const
{
    return _tetroType;
}

const Tetromino::int2* Tetromino::GetBlockCoords()
{
    return allTetromino[_tetroType][_rotation];
}

unsigned int Tetromino::GetColor()
{
    return allRgba[_tetroType];
}

unsigned int Tetromino::GetTypeColor(int tetroType)
{
    return allRgba[tetroType];
}

void Tetromino::TurnLeft()
{
    if (_rotation == 3) {_rotation = -1;}
    _rotation += 1;
}

void Tetromino::TurnRight()
{
    if (_rotation == 0) {_rotation = 4;}
    _rotation -= 1;
}

void Tetromino::MoveLeft()
{
    _x -= 1;
    if (_x <= 0) {_x = 1;}
}

void Tetromino::MoveRight()
{
    _x += 1;
    if (_x >= _xLim - 1) {_x = _xLim - 2;}
}

void Tetromino::Drop()
{
    _y += _speed;
}

void Tetromino::BackStep()
{
    _y -= 1;
}

int Tetromino::PosX() const
{
    return static_cast<int>(_x);
}

int Tetromino::PosY() const
{
    return static_cast<int>(_y);
}