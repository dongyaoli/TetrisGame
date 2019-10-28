#include "game.h"

// Game::Game(std::size_t grid_width, std::size_t grid_height)
//     : snake(grid_width, grid_height),
//       engine(dev()),
//       random_w(0, static_cast<int>(grid_width)),
//       random_h(0, static_cast<int>(grid_height)) {
//   PlaceFood();
// }

static const unsigned int s_kFieldWidth = 10;
static const unsigned int s_kFieldHeight = 20;

static bool IsOutside(const TetrominoInstance &tetro, int height)
{
    if (tetro.m_pos.y >= height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Game::Game(std::size_t grid_width, std::size_t grid_height,
           std::size_t screen_width, std::size_t screen_height) 
{
    _field.width = screen_width;
    _field.height = screen_height;
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

    while (running)
    {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.

        // controller.HandleInput(const &_activeTetro);
        controller.HandleInput(running, _activeTetro);
        Update();
        // renderer.Render(_field, _activeTetro);
        renderer.Render(_activeTetro);

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
    }
}

// return true if there was room to spawn
bool Game::SpawnTetronimo()
{
    _activeTetro.tetrominoType = (TetrominoType)(rand() % kNumTetrominoTypes);
    _activeTetro.rotation = 0;
    _activeTetro.m_pos.x = (_field.width - 4) / 2; // tetronimo block width approx = 4
    _activeTetro.m_pos.y = 0;
    return true;
}

// void Game::PlaceFood() {
//   int x, y;
//   while (true) {
//     x = random_w(engine);
//     y = random_h(engine);
//     // Check that the location is not occupied by a snake item before placing
//     // food.
//     if (!snake.SnakeCell(x, y)) {
//       food.x = x;
//       food.y = y;
//       return;
//     }
//   }
// }

void Game::Update()
{
    // hard drop

    // TetrominoInstance testInstance = m_activeTetromino;
    // while (!IsOverlap(testInstance, m_field))
    // {
    //     ++testInstance.m_pos.y;
    //     ++m_numUserDropsForThisTetronimo;
    // }
    // --testInstance.m_pos.y; // back up one
    // --m_numUserDropsForThisTetronimo;
    // AddTetronimoToField(m_field, testInstance);
    _activeTetro.m_pos.y += 1;
    if (IsOutside(_activeTetro, _field.width))
    {
        SpawnTetronimo();
    }
}

void Game::Init()
{
    _field.width = s_kFieldWidth;
    _field.height = s_kFieldHeight;
    // delete [] _field.staticBlocks;
    // _field.staticBlocks = new int[m_field.width * m_field.height];

    // for( unsigned int iy = 0; iy < _field.height; ++iy )
    // {
    // 	for( unsigned int ix = 0; ix < _field.width; ++ix )
    // 	{
    // 		_field.staticBlocks[iy * _field.width + ix] = -1;
    // 	}
    // }

    srand((unsigned int)time(NULL));
    SpawnTetronimo();
    // m_numLinesCleared = 0;
    // m_framesPerFallStep = s_initialFramesPerFallStep;
    score = 0;
}

int Game::GetScore() const { return score; }
// int Game::GetSize() const { return snake.size; }