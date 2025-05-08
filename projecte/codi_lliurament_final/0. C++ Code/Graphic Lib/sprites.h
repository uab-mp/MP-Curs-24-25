#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif





#define SPRITE_WILL_BE_ANIMATED   NULL

enum {
  SPRITES_LOOP_OFF,
  SPRITES_LOOP_ON,
};

enum {
    DO_NOT_OVERWRITE_SAME_ANIMATION,
    OVERWRITE_SAME_ANIMATION
};

//Esta estructura auxiliar sirve para poder hacer listas de frames de animaciones y sus propiedades
struct T_DESCRIPCION_FRAME_ANIMACION
{
  //! Duraci? del frame en frames de juego
  int duracion ;

  //! Posici? X del hotpoint
  int hx ;

  //! Posici? Y del hotpoint
  int hy ;

  //! Ruta del fichero que contiene el frame
  char *ruta ;
};


//! Esta estructura auxiliar sirve para poder hacer tablas de animaci?
struct T_DESCRIPCION_ANIMACION
{
  //! Este campo especifica qu?sucede cuando la animaci? llega al final: se para o comienza de nuevo.
  int modo_loop ;
  //! N?mero de frames de la animaci?
  int num_frames ;
  //! Lista terminada de punteros a frame
  struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames[11] ;
};


//! Estructura de datos que contiene la informaci? necesaria para tener en memoria una imagen y
//! poderla dibujar, y datos extra como la duraci? y el hotpoint
struct Frame
{
  int duracion ;

  SDL_Texture *texture ;

  //Puntero a un buffer de píxeles de SDL
  SDL_Surface *surface ;

  //Tamaño píxeles
  int tamx ;
  int tamy ;

  //Hotpoints
  int hx ;
  int hy ;
};


//Una animación es una lista de frames
struct T_ANIMATION
{
  //! N?mero de frames que tiene la animaci?
  int num_frames ;

  //! Este campo especifica qu?sucede cuando la animaci? llega al final: se para o comienza de nuevo.
  int tiene_loop ;

  //! Puntero a un array de punteros de frame
  struct Frame **frames ;
};

//Un sprite es un objeto de "alto nivel" que nos ayuda a trabajar con frames y animaciones
class Sprite {
public:
  Sprite(const char* ruta);
  Sprite();
  ~Sprite();
  void create(const char* ruta);
  void setScale(float scale);
  void draw(int x, int y) ;

  int getScaleY() const;
  int getScaleX() const;
private:
  //Crea una nueva animación con los .png ordenados de un directorio
  struct T_ANIMATION *CreateAnimation(T_DESCRIPCION_ANIMACION *descripcion_anim);
  //Crea un frame y devuelve el puntero
  struct Frame *CreateFrame(const char *ruta);

  //Realiza el proceso necesario en el sprite (por ejemplo la animación)
  void Tick();

  void SetAnimation(T_ANIMATION *anim, bool bOverWrite);
  void ReleaseAnimation(T_ANIMATION *anim);
  void ReleaseFrame(Frame *frame) const;
  void SetAnimationSpeed(float speed);
  void SetFrame(int num_frame);
  void SetScaleY(float scaley);
  void SetScaleX(float scalex);

  //Posición por la que vamos del frame actual de la animación
  float posicion_animacion ;
  float velocidad_animacion;
  int num_frame_actual;
  //Multiplicador de tamaño
  float scaley;
  float scalex;
  //Indica si la animación ha llegado a terminarse o no
  bool animacion_completada ;
  struct Frame *frame_actual ;
  //Puntero a la animación actual
  struct T_ANIMATION *animacion;
};
