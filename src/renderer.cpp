#include <iostream>
#include <string>
#include "renderer.h"


static SDL_Color MakeSDL_Colour( uint32_t rgba )
{
	SDL_Color color;
	color.r = (unsigned char)( ( rgba >> 24 ) & 0xff );
	color.g = (unsigned char)( ( rgba >> 16 ) & 0xff );
	color.b = (unsigned char)( ( rgba >> 8 ) & 0xff );
	color.a = (unsigned char)( ( rgba >> 0 ) & 0xff );		// alpha
	return color;
}

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(TetrominoInstance activeTetro)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  static unsigned int blockSizePixels = 32;
//   for (unsigned int iy = 0; iy < field.height; ++iy)
//   {
//     const unsigned int y = iy * blockSizePixels;
//     for (unsigned int ix = 0; ix < field.width; ++ix)
//     {
//       const unsigned int x = ix * blockSizePixels;
//       DrawRect(x, y, blockSizePixels, blockSizePixels, 0x404040ff);
//     }
//   }

  // draw active tetromino
  for (unsigned int i = 0; i < 4; ++i)
  {
    const Tetromino &tetro = s_tetrominos[activeTetro.tetrominoType];
    const Tetromino::BlockCoords &blockCoords = tetro.blockCoord[activeTetro.rotation];
    unsigned int tetrominoRgba = tetro.rgba;
    const unsigned int x = (activeTetro.m_pos.x + blockCoords[i].x) * blockSizePixels;
    const unsigned int y = (activeTetro.m_pos.y + blockCoords[i].y) * blockSizePixels;
    DrawSolidRect(x, y, blockSizePixels, blockSizePixels, tetrominoRgba);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

// void Renderer::Render(Field field, TetrominoInstance activeTetro)
// {
//   static unsigned int blockSizePixels = 32;
//   for (unsigned int iy = 0; iy < field.height; ++iy)
//   {
//     const unsigned int y = iy * blockSizePixels;
//     for (unsigned int ix = 0; ix < field.width; ++ix)
//     {
//       const unsigned int x = ix * blockSizePixels;

//       // const int blockState = field.staticBlocks[iy * m_field.width + ix];
//       // unsigned int blockRgba = 0x202020ff;
//       // if( blockState != -1 )
//       // {
//       // 	HP_ASSERT( blockState < kNumTetrominoTypes );
//       // 	blockRgba = s_tetrominos[blockState].rgba;
//       // }

//       // renderer.DrawSolidRect( x, y, blockSizePixels, blockSizePixels, blockRgba );
//       DrawRect(x, y, blockSizePixels, blockSizePixels, 0x404040ff);
//     }
//   }

//   // draw active tetromino
//   for (unsigned int i = 0; i < 4; ++i)
//   {
//     const Tetromino &tetro = s_tetrominos[activeTetro.tetrominoType];
//     const Tetromino::BlockCoords &blockCoords = tetro.blockCoord[activeTetro.rotation];
//     unsigned int tetrominoRgba = tetro.rgba;
//     const unsigned int x = (activeTetro.m_pos.x + blockCoords[i].x) * blockSizePixels;
//     const unsigned int y = (activeTetro.m_pos.y + blockCoords[i].y) * blockSizePixels;
//     DrawSolidRect(x, y, blockSizePixels, blockSizePixels, tetrominoRgba);
//   }

//   // char text[128];
//   // snprintf(text, sizeof(text), "Lines: %u", m_numLinesCleared);
//   // renderer.DrawText(text, 0, 100, 0xffffffff);
//   // snprintf(text, sizeof(text), "Level: %u", m_level);
//   // renderer.DrawText(text, 0, 140, 0xffffffff);
//   // snprintf(text, sizeof(text), "Score: %u", m_score);
//   // renderer.DrawText(text, 0, 180, 0xffffffff);
//   // snprintf(text, sizeof(text), "High score: %u", m_hiScore);
//   // renderer.DrawText(text, 0, 220, 0xffffffff);
// }



// for( unsigned int iy = 0; iy < m_field.height; ++iy )
// 	{
// 		const unsigned int y = fieldOffsetPixelsY + iy * blockSizePixels;

// 		for( unsigned int ix = 0; ix < m_field.width; ++ix )
// 		{
// 			const unsigned int x = fieldOffsetPixelsX + ix * blockSizePixels;

// 			const int blockState = m_field.staticBlocks[iy * m_field.width + ix];
// 			unsigned int blockRgba = 0x202020ff;
// 			if( blockState != -1 )
// 			{
// 				HP_ASSERT( blockState < kNumTetrominoTypes );
// 				blockRgba = s_tetrominos[blockState].rgba;
// 			}

// 			renderer.DrawSolidRect( x, y, blockSizePixels, blockSizePixels, blockRgba );
// 			renderer.DrawRect( x, y, blockSizePixels, blockSizePixels, 0x404040ff );
// 		}
// 	}

// void Renderer::Render(Snake const snake, SDL_Point const &food) {
//   SDL_Rect block;
//   block.w = screen_width / grid_width;
//   block.h = screen_height / grid_height;

//   // Clear screen
//   SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
//   SDL_RenderClear(sdl_renderer);

//   // Render food
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
//   block.x = food.x * block.w;
//   block.y = food.y * block.h;
//   SDL_RenderFillRect(sdl_renderer, &block);

//   // Render snake's body
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//   for (SDL_Point const &point : snake.body) {
//     block.x = point.x * block.w;
//     block.y = point.y * block.h;
//     SDL_RenderFillRect(sdl_renderer, &block);
//   }

//   // Render snake's head
//   block.x = static_cast<int>(snake.head_x) * block.w;
//   block.y = static_cast<int>(snake.head_y) * block.h;
//   if (snake.alive) {
//     SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
//   } else {
//     SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
//   }
//   SDL_RenderFillRect(sdl_renderer, &block);

//   // Update Screen
//   SDL_RenderPresent(sdl_renderer);
// }

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


void Renderer::DrawRect( int x, int y, int w, int h, uint32_t rgba /*= 0xffffffff */ )
{
	SDL_Color color = MakeSDL_Colour( rgba );
	SDL_SetRenderDrawColor( sdl_renderer, color.r, color.g, color.b, color.a );

	SDL_Rect rect = {x, y, w, h};
	SDL_RenderDrawRect( sdl_renderer, &rect );
}

void Renderer::DrawSolidRect( int x, int y, int w, int h, uint32_t rgba /*= 0xffffffff */ )
{
	SDL_Color color = MakeSDL_Colour( rgba );
	SDL_SetRenderDrawColor( sdl_renderer, color.r, color.g, color.b, color.a );

	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect( sdl_renderer, &rect );
}