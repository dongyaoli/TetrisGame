#ifndef TETROMINO_H
#define TETROMINO_H

struct uint2
{
	unsigned int x;
	unsigned int y;
};

struct int2
{
	int x;
	int y;
};

struct Field
{
	unsigned int width;
	unsigned int height;
};

enum TetrominoType
{
	kTetrominoType_I = 0,
 	kTetrominoType_J,
	kTetrominoType_L,
	kTetrominoType_O,
	kTetrominoType_S,
	kTetrominoType_T,
	kTetrominoType_Z,
	kNumTetrominoTypes
};

struct TetrominoInstance
{
	TetrominoType tetrominoType;
	int2 m_pos;
	unsigned int rotation;
};

struct Tetromino
{
	static const unsigned int kNumBlocks = 4;
	static const unsigned int kNumRotations = 4;
	typedef uint2 BlockCoords[kNumBlocks];
    
	BlockCoords blockCoord[kNumRotations];
	unsigned int rgba;
};

static const Tetromino s_tetrominos[kNumTetrominoTypes] =
{
	// I
	{
		0, 1, 1, 1, 2, 1, 3, 1,
		2, 0, 2, 1, 2, 2, 2, 3,
		0, 2, 1, 2, 2, 2, 3, 2,
		1, 0, 1, 1, 1, 2, 1, 3,
		0x00ffffff,
	},
	// J
	{
		0, 0, 0, 1, 1, 1, 2, 1,
		1, 0, 2, 0, 1, 1, 1, 2,
		0, 1, 1, 1, 2, 1, 2, 2,
		1, 0, 1, 1, 0, 2, 1, 2,
		0x0000ffff,
	},
	// L
	{
		2, 0, 0, 1, 1, 1, 2, 1,
		1, 0, 1, 1, 1, 2, 2, 2,
		0, 1, 1, 1, 2, 1, 0, 2,
		0, 0, 1, 0, 1, 1, 1, 2,
		0xffaa00ff,
	},
	// O
	{
		1, 0, 2, 0, 1, 1, 2, 1,
		1, 0, 2, 0, 1, 1, 2, 1,
		1, 0, 2, 0, 1, 1, 2, 1,
		1, 0, 2, 0, 1, 1, 2, 1,
		0xffff00ff
	},
	// S
	{
		1, 0, 2, 0, 0, 1, 1, 1,
		1, 0, 1, 1, 2, 1, 2, 2,
		1, 1, 2, 1, 0, 2, 1, 2,
		0, 0, 0, 1, 1, 1, 1, 2,
		0x00ff00ff,
	},
	// T
	{
		1, 0, 0, 1, 1, 1, 2, 1,
		1, 0, 1, 1, 2, 1, 1, 2,
		0, 1, 1, 1, 2, 1, 1, 2,
		1, 0, 0, 1, 1, 1, 1, 2,
		0x9900ffff,
	},
	// Z
	{
		0, 0, 1, 0, 1, 1, 2, 1,
		2, 0, 1, 1, 2, 1, 1, 2,
		0, 1, 1, 1, 1, 2, 2, 2,
		1, 0, 0, 1, 1, 1, 0, 2,
		0xff0000ff,
	}
};

// class Tetromino 
// {
// public:
//     Tetromino();
//     int2 _pos;
//     int _rotation;
//     TetrominoType _tetroType;
// 	unsigned int rgba;

// private:
// };

// struct Tetromino
// {
// 	static const unsigned int kNumBlocks = 4;
// 	static const unsigned int kNumRotations = 4;
// 	typedef uint2 BlockCoords[kNumBlocks];
    
// 	BlockCoords blockCoord[kNumRotations];
// 	unsigned int rgba;
// };

// struct TetrominoInstance
// {
// 	TetrominoType m_tetrominoType;
// 	int2 m_pos;
// 	unsigned int m_rotation;
// };

#endif // TETROMINO_H