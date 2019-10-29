#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "tetro.h"

class Renderer
{
public:
  Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
           const std::size_t gridSize);
  ~Renderer();

  void Render(Tetromino const activeTetro, std::unique_ptr<int[]> &staticBlock);
  void UpdateWindowTitle(int score, int fps);
  void GameoverWindowTitle(int score);
  void DrawRect( int x, int y, int w, int h, uint32_t rgba = 0xffffffff );
  void DrawSolidRect( int x, int y, int w, int h, uint32_t rgba = 0xffffffff );
  void DrawText( const char* text, int x, int y, uint32_t rgba = 0xffffffff );

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t gridSize;
};

#endif // RENDERER_H