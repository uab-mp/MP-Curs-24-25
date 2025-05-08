#include "keyboard.h"
#include "mouse.h"
#include "video.h"
#include "error.h"

#include <iostream>

#ifdef _WIN32
  #include <windows.h>
  // Esto puede parecer extra?, pero es necesario si el proyecto 
  // es de "l?ea de comandos" en Visual Studio y vamos a usar SDL  
  #undef main
#endif


struct DatosVideo g_Video ;

Screen::Screen(unsigned int a, unsigned int b) 
    : resolucioX(a), resolucioY(b)
{
  //inicialització llibreria gràfica
  SDL_SetMainReady();
  SDL_Init(SDL_INIT_VIDEO);
  ScreenStatus.exit = false;
  ScreenStatus.minimized = 0;
  ScreenStatus.currentFrameNumber = 0;
  init();
}

Screen::Screen() 
    : resolucioX(600), resolucioY(550)
{
  //inicialització llibreria gràfica
  SDL_SetMainReady();
  SDL_Init(SDL_INIT_VIDEO);
  ScreenStatus.exit = false;
  ScreenStatus.minimized = 0;
  ScreenStatus.currentFrameNumber = 0;
  init();
}

Screen::~Screen()
{
  SDL_DestroyRenderer(g_Video.renderer) ;
  SDL_DestroyWindow(g_Video.window) ;
  g_Video.renderer = nullptr;
  g_Video.window = nullptr;
  SDL_Quit();
}

void Screen::show()
{
  // Muestra la ventana
  SDL_ShowWindow(g_Video.window) ;
}

void Screen::processEvents()
{
  // Borramos el buffer de vídeo antes de hacer la espera porque así aprovechamos mejor
  // el tiempo en vez de esperar para luego ponernos a borrar cuando nos toca procesar
  clearBackBuffer(255, 255, 0) ;

  //Procesamos teclado y mouse
  Keyboard_Tick() ;
  Mouse_Tick() ;

  // Procesamos los eventos que pueda habernos metido en la cola el sistema operativo
  processEventSystem() ;
}


void Screen::update()
{
  // Incrementamos el n?mero de frame actual
  ScreenStatus.currentFrameNumber++ ;

  // Pedimos al sistema operativo que actualice el contenido de la ventana
  flip() ;

}

void Screen::init()
{
  // Pedimos que se inicialice la ventana del juego y establecemos como límite mínimo MAX_FPS
  initializeHardware(resolucioX, resolucioY, MAX_FPS, RUN_IN_WINDOW_MODE);

#ifdef _WIN32
  //Alta prioridad, mejora la estabilidad del dibujado y el sonido
  SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS) ;
#endif
}

bool Screen::isExit() const
{
  return ScreenStatus.exit;
}

// Inicializa la ventana con el tamaño especificado
void Screen::init(int new_resx, int new_resy, bool FullScreen)
{
  Uint32 flags = SDL_WINDOW_HIDDEN ;/*SDL_WINDOW_OPENGL | */
  //flags |= SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_MAXIMIZED*/ ;

  if(FullScreen) 
  {
    flags |= SDL_WINDOW_FULLSCREEN ;
  }

  g_Video.resx = new_resx ;
  g_Video.resy = new_resy ;

  // Create the window where we will draw.
  g_Video.window   = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, new_resx, new_resy, flags);
  
  #ifdef DONT_USE_SDL_RENDERER_SOFTWARE
    g_Video.renderer = SDL_CreateRenderer(g_Video.window, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
  #else
  g_Video.renderer = SDL_CreateRenderer(g_Video.window, -1, SDL_RENDERER_SOFTWARE);//En virtual box crashea si no es este flag
  #endif

  if (!g_Video.renderer) 
    throw custom_error("[Game::Video_Init] No se ha podido crear la ventana para renderizar", __FILE__, __LINE__);
  //{
  //  SDL_Rect rect ;
  //
  //  rect.h = new_resx ;
  //  rect.w = new_resy ;
  //
  //  rect.x = 0 ;
  //  rect.y = 0 ;
  //
  //  SDL_RenderSetViewport(g_Video.renderer, &rect) ;
  //}
}

// Borra el buffer de vídeo
void Screen::clearBackBuffer(int r, int g, int b)
{
 SDL_SetRenderDrawColor(g_Video.renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255) ;
 SDL_RenderClear(g_Video.renderer) ;
}

void Screen::processEventSystem()
{
  SDL_Event e;
  // Mientras haya eventos en la cola nos quedamos en el bucle y los procesamos
  while (SDL_PollEvent(&e)) 
  {
    // Application events        
    if(e.type == SDL_QUIT)   ScreenStatus.exit = true;
       
    // Window events        
    else if(e.type == SDL_WINDOWEVENT)
    {
      if(e.window.event == SDL_WINDOWEVENT_MINIMIZED)   ScreenStatus.minimized = true;            
      else if(e.window.event == SDL_WINDOWEVENT_RESTORED)    ScreenStatus.minimized = false;
    }

    // Keyboard events
    else if(e.type == SDL_KEYDOWN) 
    {
      // Quitar comentario si s?o queremos hacemos caso de pulsaciones "reales" y no producto de los settings de repetici?
//        if(!event.key.repeat) {
        Keyboard_ProcessKeyDown(e.key.keysym.sym) ;
//        }
    }
    else if(e.type ==  SDL_KEYUP)    Keyboard_ProcessKeyUp(SDL_GetScancodeFromKey(e.key.keysym.sym)) ;
      
    // Mouse events

    /**< Mouse button pressed */
    else if(e.type == SDL_MOUSEBUTTONDOWN)   Mouse_ProcessButtonDown(e.button.button);      
    /**< Mouse button released */  
    else if(e.type == SDL_MOUSEBUTTONUP)     Mouse_ProcessButtonUp(e.button.button);
    /**< Mouse wheel motion */
    else if(e.type == SDL_MOUSEWHEEL)        Mouse_ProcessWheel(e.wheel.x, e.wheel.y) ;       
  }
}


void Screen::flip()
{
  // Pide al sistema operativo que actualice el contenido visible de la ventana
  SDL_RenderPresent(g_Video.renderer) ;
}

void Screen::initializeHardware(int new_resolution_x, int new_resolution_y, int fps_maximos, bool FullScreen)
{
  if (SDL_Init( SDL_INIT_VIDEO) != 0 ) 
    throw custom_error( std::string("Unable to init SDL: ") + std::string(SDL_GetError()) , __FILE__, __LINE__);

  Keyboard_Init();
  Mouse_Init();
  init(new_resolution_x, new_resolution_y, FullScreen);
}
