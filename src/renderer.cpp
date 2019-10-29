#include <iostream>
#include <string>
#include "renderer.h"

static SDL_Color MakeSDL_Colour(uint32_t rgba)
{
  SDL_Color color;
  color.r = (unsigned char)((rgba >> 24) & 0xff);
  color.g = (unsigned char)((rgba >> 16) & 0xff);
  color.b = (unsigned char)((rgba >> 8) & 0xff);
  color.a = (unsigned char)((rgba >> 0) & 0xff);
  return color;
}

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t gridSize)
    : screen_width(screen_width),
      screen_height(screen_height),
      gridSize(gridSize)
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

void Renderer::Render(Tetromino activeTetro, std::unique_ptr<int[]> &staticBlocks)
{
  SDL_Rect block;
  block.w = screen_width / gridSize;
  block.h = screen_height / gridSize;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  for (unsigned int iy = 0; iy < block.h; iy++)
  {
    const unsigned int y = iy * gridSize;

    for (unsigned int ix = 0; ix < block.w; ix++)
    {
      const unsigned int x = ix * gridSize;

      const int blockState = staticBlocks[iy * block.w + ix];
      unsigned int blockRgba = 0x202020ff;
      if (blockState != -1)
      {
        blockRgba = activeTetro.GetTypeColor(blockState);
      }

      DrawSolidRect(x, y, gridSize, gridSize, blockRgba);
      DrawRect(x, y, gridSize, gridSize, 0x404040ff);
    }
  }

  // draw active tetromino
  const Tetromino::int2 *blockCoords = activeTetro.GetBlockCoords();
  unsigned int tetrominoRgba = activeTetro.GetColor();
  for (unsigned int i = 0; i < 4; ++i)
  {
    const unsigned int x = (activeTetro.PosX() + blockCoords[i].x) * gridSize;
    const unsigned int y = (activeTetro.PosY() + blockCoords[i].y) * gridSize;
    DrawSolidRect(x, y, gridSize, gridSize, tetrominoRgba);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::GameoverWindowTitle(int score)
{
  std::string title{"Game Over with Score: " + std::to_string(score)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::DrawRect(int x, int y, int w, int h, uint32_t rgba)
{
  SDL_Color color = MakeSDL_Colour(rgba);
  SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);

  SDL_Rect rect = {x, y, w, h};
  SDL_RenderDrawRect(sdl_renderer, &rect);
}

void Renderer::DrawSolidRect(int x, int y, int w, int h, uint32_t rgba)
{
  SDL_Color color = MakeSDL_Colour(rgba);
  SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);

  SDL_Rect rect = {x, y, w, h};
  SDL_RenderFillRect(sdl_renderer, &rect);
}