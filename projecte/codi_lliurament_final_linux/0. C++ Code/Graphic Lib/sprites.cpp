#include <cstdlib>
#include <cassert>

#include "image_png.h"
#include "video.h"
#include "sprites.h"
#include "error.h"

Sprite::Sprite()
{
    animacion = NULL;
    velocidad_animacion = 1.0f;
    posicion_animacion = 0.0f;
    num_frame_actual = 0;
    animacion_completada = false;
    setScale(1.0f);
    frame_actual = NULL;
}

Sprite::Sprite(const char *ruta)
{
  //Inicializamos
  animacion = NULL;

  // Por defecto cada frame dura... Un frame :-)
  velocidad_animacion = 1.0f ;
  setScale(1.0f) ;

  if(ruta != SPRITE_WILL_BE_ANIMATED)
  {
    // Si no es NULL, creamos un frame para contener la imagen que toque
    frame_actual = CreateFrame(ruta) ;
  } // Si recibimos un NULL, queremos un sprite "vacio" para ponerle luego animaciones
}

Sprite::~Sprite()
{
  if(animacion == NULL)
  {
    // Si el sprite no tiene animación es que solo tiene su frame actual
    // Si el frame tiene un handle de textura pedimos al hardware que se olvide de la imagen y
    // libere la memoria y los handles que haya podido alojar
    if(frame_actual->texture) SDL_DestroyTexture(frame_actual->texture);

    // Si el frame tiene una surface de SDL la liberamos
    if(frame_actual->surface) SDL_FreeSurface(frame_actual->surface);

    //Limpiamos el resto
    delete frame_actual;
  } // Si el sprite tiene animación no hacemos nada, las animaciones se tienen que liberar a mano
  IMG_Quit();
}

struct T_ANIMATION *Sprite::CreateAnimation(struct T_DESCRIPCION_ANIMACION *descripcion_anim)
{
  assert(descripcion_anim) ;

  T_ANIMATION *anim = new T_ANIMATION();

  anim->frames = new Frame*() ;
  anim->num_frames = descripcion_anim->num_frames ;
  anim->tiene_loop = descripcion_anim->modo_loop ;

  T_DESCRIPCION_FRAME_ANIMACION *descripcion_frame;
  for(int var_frame = 0; var_frame < descripcion_anim->num_frames; var_frame++) {

    descripcion_frame = descripcion_anim->descripcion_frames[var_frame] ;

    anim->frames[var_frame] = CreateFrame(descripcion_frame->ruta) ;

    anim->frames[var_frame]->duracion = descripcion_frame->duracion ;
    anim->frames[var_frame]->hx       = descripcion_frame->hx ;
    anim->frames[var_frame]->hy       = descripcion_frame->hy ;
  }
  return anim ;
}

void Sprite::SetAnimation(struct T_ANIMATION *anim, bool OverWrite)
{
  assert(anim);

  //No podemos permitir que si el sprite esta gestionando un frame por su cuenta se pierda en el limbo.
  //Si la animacion es NULL el frame actual no puede serlo
  if(animacion == NULL)
  {
    assert( frame_actual == NULL);
  }

  if(OverWrite || anim != animacion)
  {
      animacion = anim ;
      frame_actual = anim->frames[0] ;
      num_frame_actual = 0 ;
      posicion_animacion = 0 ;
      animacion_completada = false ;
    }
}

void Sprite::ReleaseFrame(Frame *frame) const
{
  // Si el frame tiene un handle de textura pedimos al hardware que se olvide de la imagen y
  // libere la memoria y los handles que haya podido alojar
  if(frame->texture) SDL_DestroyTexture(frame->texture) ;

  // Si el frame tiene una surface de SDL la liberamos
  if(frame->surface) SDL_FreeSurface(frame->surface) ;
}



void Sprite::ReleaseAnimation(struct T_ANIMATION *anim)
{
  assert(anim) ;

  for(int var_frame = 0; var_frame < anim->num_frames; var_frame++)
  {
    ReleaseFrame(anim->frames[var_frame]) ;
  }

  delete anim;
}

void Sprite::SetAnimationSpeed(float speed)
{
  velocidad_animacion = speed ;
}

void Sprite::SetFrame(int num_frame)
{
  if(num_frame < 0) num_frame = 0 ;
  if(num_frame >= animacion->num_frames) num_frame = animacion->num_frames - 1 ;

  num_frame_actual = num_frame ;
   posicion_animacion = 0 ;
}

// Escala el tamaño horizontal del sprite por el factor indicado
void Sprite::SetScaleX(float new_scalex)
{
  if(new_scalex < 0.0f) new_scalex = 0.0f ;
  scalex = new_scalex ;
}

// Escala el tamaño vertical del sprite por el factor indicado
void Sprite::SetScaleY(float new_scaley)
{
  if(new_scaley < 0.0f) new_scaley = 0.0f ;
  scaley = new_scaley ;
}

// Escala el tamaño del sprite por el factor indicado
void Sprite::setScale(float scale)
{
  if(scale < 0.0f) scale = 0.0f ;

  scalex = scale ;
  scaley = scale ;
}

// Dibuja un sprite en las coordenadas especificadas
void Sprite::draw(int x, int y)
{
  //Nos aseguramos de que el vídeo está en marcha
  assert(g_Video.renderer) ;
  //Variable para que el cóigo quede más corto y legible
  Frame* frame =  frame_actual;
  // Si el sprite no tiene un frame que dibujar nos marchamos
  if(frame == NULL) return ;
  if(frame->surface == NULL) return ;


  // Nos aseguramos de que el sprite tiene textura
  assert(frame->texture) ;

  // La SDL necesita que le especifiquemos un par de rectángulos en su formato para poder dibujar
  SDL_Rect srcrect ;
  SDL_Rect dstrect ;

  // Posición de la esquina superior izquierda
  srcrect.x = 0 ;
  srcrect.y = 0 ;

  // Número de píxels a leer
  srcrect.w = frame->tamx;
  srcrect.h = frame->tamy ;

  // Posición de la esquina superior izquierda al dibujar
  dstrect.x = x - static_cast<int>(frame->hx * scalex) ;
  dstrect.y = y - static_cast<int>(frame->hy * scaley) ;

  // Tamáño visible al dibujar
  dstrect.w = static_cast<int>(frame->tamx * scalex) ;
  dstrect.h = static_cast<int>(frame->tamy * scaley) ;

  SDL_RenderCopy(g_Video.renderer, frame->texture, &srcrect, &dstrect) ;
}

// Crea un sprite, vacío si ruta == SPRITE_WILL_BE_ANIMATED, o con un frame conteniendo el .png
// situado en la ruta
void Sprite::create(const char *ruta)
{
  //Inicializamos
  animacion = NULL;

  // Por defecto cada frame dura... Un frame :-)
  velocidad_animacion = 1.0f ;
  setScale(1.0f) ;

  if(ruta != SPRITE_WILL_BE_ANIMATED)
  {
    // Si no es NULL, creamos un frame para contener la imagen que toque
    frame_actual = CreateFrame(ruta) ;
  } // Si recibimos un NULL, queremos un sprite "vacio" para ponerle luego animaciones
}

int Sprite::getScaleY() const
{
  return frame_actual->tamy;
}

int Sprite::getScaleX() const
{
  return frame_actual->tamx;
}

void Sprite::Tick()
{
  T_ANIMATION *new_animacion;

  new_animacion = animacion;
  if(animacion == NULL) return ;

  posicion_animacion += velocidad_animacion ;

  while( posicion_animacion >= new_animacion->frames[num_frame_actual]->duracion)
  {
    posicion_animacion -= new_animacion->frames[num_frame_actual]->duracion ;
    num_frame_actual++ ;

    if(num_frame_actual >= new_animacion->num_frames)
    {
      animacion_completada = true ;

      if(new_animacion->tiene_loop) num_frame_actual = 0 ;
      else num_frame_actual = new_animacion->num_frames - 1 ;
    }
  }
   frame_actual = new_animacion->frames[num_frame_actual] ;
}

Frame* Sprite::CreateFrame(const char *ruta)
{
  assert(ruta) ;

  Frame* frame = new Frame();

  //Lee el tamaño de X e Y
  read_png_file(ruta, &frame->tamx, &frame->tamy) ;

  frame->surface = IMG_Load(ruta);
  if(frame->surface == NULL)
    throw custom_error("[Sprite::CreateFrame] No se ha podido cargar la imágen");

  // Creamos el handle de textura de hardware
  frame->texture = SDL_CreateTextureFromSurface(g_Video.renderer, frame->surface) ;

  // Indicamos al hardware de que este sprite va a necesitar c?culos de alpha blending (para que no se vea el rect?gulo donde no hay dibujo)
  SDL_SetTextureBlendMode(frame->texture, SDL_BLENDMODE_BLEND);

  return frame;
}
