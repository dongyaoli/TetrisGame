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
	bool Update();
	void Init();

private:
	int _fieldWidth;
	int _fieldHeight;
	Tetromino _activeTetro{0, 0, 0, 0, 0};
	bool Overlap();
	void MergeActive();
	int ClearFull();
	std::unique_ptr<int[]> _staticBlocks;

	std::random_device dev;
	std::mt19937 engine;
	std::uniform_int_distribution<int> random_w;
	std::uniform_int_distribution<int> random_h;

	int score{0};
	float speed{0.1};
	bool SpawnTetronimo();
};

#endif