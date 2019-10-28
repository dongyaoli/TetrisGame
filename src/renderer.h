#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "tetromino.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  // void Render(Field const field, TetrominoInstance const activeTetro);
  void Render(TetrominoInstance const activeTetro);
  void UpdateWindowTitle(int score, int fps);
  void DrawRect( int x, int y, int w, int h, uint32_t rgba = 0xffffffff );
  void DrawSolidRect( int x, int y, int w, int h, uint32_t rgba = 0xffffffff );

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  // SDL_Renderer *m_pSdlRenderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif // RENDERER_H