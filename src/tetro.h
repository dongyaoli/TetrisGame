#ifndef TETROMINO_H
#define TETROMINO_H

struct Field
{
	unsigned int width;
	unsigned int height;
};

class Tetromino 
{
public:
    static const int numTetroTypes = 7;
    struct int2
    {
        int x;
        int y;
    };
    int PosX() const;
    int PosY() const;
    typedef int2 BlockCoords[4];
    Tetromino(int tetroType, int rotation, float x, float y, int xLim);
    Tetromino();
    void SetType(int newType);
    void SetRotation(int newRotation);
    void SetXLim(int xLim);
    int GetTetroType() const;
    void BackStep();
    
    const int2* GetBlockCoords();
    unsigned int GetColor();
    unsigned int GetTypeColor(int tetroType);
    void TurnLeft();
    void TurnRight();
    void MoveLeft();
    void MoveRight();
    void Drop();

private:
    int _rotation;
    int _tetroType;
    float _x;
    float _y;
    int _xLim;
    float _speed{0.1};
    static constexpr BlockCoords allTetromino[7][4] = 
    {
        // I
        {
            0, 1, 1, 1, 2, 1, 3, 1,
            2, 0, 2, 1, 2, 2, 2, 3,
            0, 2, 1, 2, 2, 2, 3, 2,
            1, 0, 1, 1, 1, 2, 1, 3,
        },
        // J
        {
            0, 0, 0, 1, 1, 1, 2, 1,
            1, 0, 2, 0, 1, 1, 1, 2,
            0, 1, 1, 1, 2, 1, 2, 2,
            1, 0, 1, 1, 0, 2, 1, 2,
        },
        // L
        {
            2, 0, 0, 1, 1, 1, 2, 1,
            1, 0, 1, 1, 1, 2, 2, 2,
            0, 1, 1, 1, 2, 1, 0, 2,
            0, 0, 1, 0, 1, 1, 1, 2,
        },
        // O
        {
            1, 0, 2, 0, 1, 1, 2, 1,
            1, 0, 2, 0, 1, 1, 2, 1,
            1, 0, 2, 0, 1, 1, 2, 1,
            1, 0, 2, 0, 1, 1, 2, 1,
        },
        // S
        {
            1, 0, 2, 0, 0, 1, 1, 1,
            1, 0, 1, 1, 2, 1, 2, 2,
            1, 1, 2, 1, 0, 2, 1, 2,
            0, 0, 0, 1, 1, 1, 1, 2,
        },
        // T
        {
            1, 0, 0, 1, 1, 1, 2, 1,
            1, 0, 1, 1, 2, 1, 1, 2,
            0, 1, 1, 1, 2, 1, 1, 2,
            1, 0, 0, 1, 1, 1, 1, 2,
        },
        // Z
        {
            0, 0, 1, 0, 1, 1, 2, 1,
            2, 0, 1, 1, 2, 1, 1, 2,
            0, 1, 1, 1, 1, 2, 2, 2,
            1, 0, 0, 1, 1, 1, 0, 2,
	    }   
    };
    static constexpr unsigned int allRgba[7] = 
    {
       0x00ffffff,
       0x0000ffff,
       0xffaa00ff,
       0xffff00ff,
       0x00ff00ff,
       0x9900ffff,
       0xff0000ff,
    };
};

#endif // TETROMINO_H