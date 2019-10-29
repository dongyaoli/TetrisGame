#include "game.h"


static bool IsOutside(const Tetromino &tetro, int height)
{
    int pos = tetro.PosY();
    if (pos >= height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Game::Game(std::size_t gridSize, std::size_t screenWidth, std::size_t screenHeight) 
{
    _fieldWidth = screenWidth / gridSize;
    _fieldHeight = screenHeight / gridSize;
};

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;
    Init();
    bool gameContinue = true;

    while (running)
    {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.

        controller.HandleInput(running, _activeTetro);
        gameContinue = Update();
        renderer.Render(_activeTetro, _staticBlocks);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000)
        {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration)
        {
            SDL_Delay(target_frame_duration - frame_duration);
        }
        if (!gameContinue) break;
    }
    if (!gameContinue) {
        renderer.GameoverWindowTitle(score);
        SDL_Delay(5000);
    }
}

// return true if there was room to spawn
bool Game::SpawnTetronimo()
{
    int x = (_fieldWidth - 4) / 2;
    int y = 0;
    _activeTetro = Tetromino(rand(), rand(), x, y, _fieldWidth);
    if (Overlap()) return false;
    else return true;
}

bool Game::Update()
{
    _activeTetro.Drop();

    if (Overlap())
    {
        _activeTetro.BackStep();
        MergeActive();
        if (!SpawnTetronimo()) {
            MergeActive();
            return false;
        }
        int s = ClearFull();
        score += s;
    }
    return true;
}

void Game::Init()
{
    _staticBlocks = std::unique_ptr<int[]>{new int[_fieldWidth * _fieldHeight]};
    for( unsigned int iy = 0; iy < _fieldHeight; ++iy )
	{
		for( unsigned int ix = 0; ix < _fieldWidth; ++ix )
		{
			_staticBlocks[iy * _fieldWidth + ix] = -1;
		}
	}
    srand((unsigned int)time(NULL));
    SpawnTetronimo();
    score = 0;
}

bool Game::Overlap()
{
    const Tetromino::int2* blockCoords = _activeTetro.GetBlockCoords();
    for( int i = 0; i < 4; i++)
	{
		const int x = _activeTetro.PosX() + blockCoords[i].x;
		const int y = _activeTetro.PosY() + blockCoords[i].y;

        if (y >= _fieldHeight) return true;
		if(_staticBlocks[x + y * _fieldWidth] != -1) return true;
	}

	return false;
}

void Game::MergeActive()
{
    const Tetromino::int2* blockCoords = _activeTetro.GetBlockCoords();
	for( unsigned int i = 0; i < 4; i++ )
	{
		const int x = _activeTetro.PosX() + blockCoords[i].x;
		const int y = _activeTetro.PosY() + blockCoords[i].y;
		_staticBlocks[x + y * _fieldWidth] = _activeTetro.GetTetroType();
	}
}

int Game::ClearFull()
{
    int numLinesCleared = 0;
	for(int y = 0; y < _fieldHeight; y++ )
	{
		bool bRowFull = true;
		for( unsigned int x = 0; x < _fieldWidth; x++ )
		{
			if( _staticBlocks[x + y * _fieldWidth] == -1 )
			{
				bRowFull = false;
				break;
			}
		}

		if( bRowFull )
		{
			++numLinesCleared;
			for(int yy = y; yy > 0; --yy )
			{
				for(int x = 0; x < _fieldWidth; ++x )
				{
					_staticBlocks[x + yy * _fieldWidth] = _staticBlocks[x + ( yy - 1 ) * _fieldWidth];
				}
			}
		}
	}
    return numLinesCleared;
}

int Game::GetScore() const { return score; }