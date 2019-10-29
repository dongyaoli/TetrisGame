#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "tetro.h"

class Game
{
public:
	Game(std::size_t gridSize, std::size_t screenWidth, std::size_t screenHeight);
	void Run(Controller const &controller, Renderer &renderer,
			 std::size_t target_frame_duration);
	int GetScore() const;
	void Update();
	void Init();
	// int GetSize() const;

private:
	// state
	// Field _field;
	int _fieldWidth;
	int _fieldHeight;
	Tetromino _activeTetro{0, 0, 0, 0, 0};
	bool Overlap();
	void MergeActive();
	std::unique_ptr<int[]> _staticBlocks;

	std::random_device dev;
	std::mt19937 engine;
	std::uniform_int_distribution<int> random_w;
	std::uniform_int_distribution<int> random_h;

	int score{0};
	float speed{0.1};

	// void InitPlaying();
	// void UpdatePlaying(const GameInput &gameInput);
	// void DrawPlaying(Renderer &renderer);

	bool SpawnTetronimo();
	// void AddTetronimoToField(const Field &field, const TetrominoInstance &tetronimoInstance);
};

#endif