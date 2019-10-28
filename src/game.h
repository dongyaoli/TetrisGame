#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "tetromino.h"

class Game
{
public:
	Game(std::size_t grid_width, std::size_t grid_height,
		 std::size_t screen_width, std::size_t screen_height);
	void Run(Controller const &controller, Renderer &renderer,
			 std::size_t target_frame_duration);
	int GetScore() const;
	void Update();
	void Init();
	// int GetSize() const;

private:
	// state
	Field _field;
	TetrominoInstance _activeTetro;

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