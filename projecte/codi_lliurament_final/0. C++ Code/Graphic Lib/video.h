#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif

#define ACTIVAR_CONSOLA_DE_DEBUG

static const bool RUN_IN_WINDOW_MODE     = 0;
static const bool RUN_IN_FULLSCREEN_MODE = 1;

static const int MAX_FPS     =  60;

class Screen {
public:
  //"a" = resolucioX , "b" = resolucioY
  Screen(unsigned int a, unsigned int b);
  //Default: resolucioX = 600, resolucioY = 550
  Screen();
  ~Screen();

  void show();
  void processEvents();
  void update();
  void init();
  bool isExit() const;

private:
  void initializeHardware(int new_resolution_x, int new_resolution_y, int fps_maximos, bool FullScreen);
  void init(int new_resx, int new_resy, bool FullScreen);
  void clearBackBuffer(int, int, int);
  void processEventSystem();
  void flip();

  const unsigned int resolucioX;
  const unsigned int resolucioY;
  
  struct ScreenStatus
  {
    bool exit ;
    bool minimized ;
    int currentFrameNumber;
  } ScreenStatus;

};



//! En esta estructura se guarda el status del control de v?eo
struct DatosVideo
{
  int resx ;
  int resy ;

  SDL_Window *window ;
  SDL_Renderer *renderer ;
} ;

// Extern para acceder a la variable de status de v?eo
extern struct DatosVideo g_Video ;
