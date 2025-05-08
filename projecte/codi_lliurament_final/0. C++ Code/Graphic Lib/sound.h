#pragma once

#include "stb_vorbis.h"

//! N?mero m?imo de sonidos sonando de manera simult?ea

#define MAX_SIMULTANEOUS_SOUND_CHANNELS                                  8

//! El n?mero m?imo de canales reservados a efectos de sonido es el total menos el de la m?sica y el del ambiente

#define MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS                (MAX_SIMULTANEOUS_SOUND_CHANNELS - 1 - 1)


//! Tipos de streaming
enum {
  //! Reproducir desde un buffer de memoria (Ideal para sonidos peque?s)
  PLAY_FROM_MEMORY,

  //! Reproducir cargando poco a poco desde disco (Ideal / Necesario para sonidos grandes)
  PLAY_FROM_DISK_STREAM
} ;


//! Tipos de loop
enum {
  //! Cuando le damos al play el sonido suena desde el principio si estaba parado, o contin?a por donde iba si estaba en pause
  SOUND_PLAY_NORMAL,

  //! Si el sonido ya estaba reproduci?dose lo deja continuar en vez de hacer que vuelva al principio
  SOUND_DO_NOT_RESTART_IF_ALREADY_PLAYING,

  //! El sonido vuelve a comenzar desde el principio INCLUSO si s?o estaba pausado
  SOUND_FORCE_RESTART,
} ;


//! Tipos de loop
enum {
  //! El sonido se detiene al llegar al final
  PLAY_THEN_STOP_AT_END,

  //! El sonido vuelve a comenzar cuando acaba
  PLAY_THEN_LOOP_AT_END
} ;


//! Estados en los que puede estar un sonido
enum {
  //! El sonido est?parado, y cuando comience a reproducirse de nuevo lo har?desde el principio
  SOUND_STATE_STOPPED,

  //! El sonido est?pausado, y cuando comience a reproducirse de nuevo lo har?desde donde se qued?al pausarlo
  SOUND_STATE_PAUSED,

  //! El sonido est?reproduci?dose
  SOUND_STATE_PLAYING
} ;

struct T_SOUND
{
  //! Longitud en samples del sonido
  int num_samples ;

  //! Posici? en la que se encuentra del stream
  int posicion_stream ;
	
  //! Indica el modo de loop del sonido
  int bLoop ;

  //! Indica en qu?estado se encuentra el sonido
  int estado ;

  //! Puntero al buffer de almacenamiento si se reproduce desde memoria, NULL si se reproduce desde disco
  unsigned char *buffer_fichero ;

  //! Posici? que est?ocupando en la cola, en caso de estar playe?dose
  int posicion_cola ;

  //! Puntero a una estructura de datos de la librer? stb_vorbis
  stb_vorbis *ogg ;
} ;

//! Inicializa la librer? de sonido
void Sound_Init() ;

//! Libera los recursos alojados por la librer? de sonido
void Sound_Release() ;

//struct T_SOUND *Sound_LoadFileStream(char *path, int bLoop) ;
//struct T_SOUND *Sound_LoadMemoryStream(char *path, int bLoop) ;

//! Funci? de alto nivel que automatiza la carga y reproducci? de la m?sica de fondo
struct T_SOUND *Sound_LoadMusic(char *path, int bStream) ;

//! Carga un sonido y lo deja listo para comenzar a usarlo
struct T_SOUND *Sound_LoadSound(char *path) ;

//! Comienza la reproducci? del sonido pasado como par?etro. Devuelve el n?mero de slot que emplear?el sonido para reproducirse, o NO_SOUND_CHANNEL_AVAILABLE si no queda ninguno libre
int Sound_Play(struct T_SOUND *sonido, int mode) ;

//! Pausa la reproducci? del sonido pasado como par?etro
void Sound_Pause(struct T_SOUND *sonido) ;

//! Detiene la reproducci? del sonido pasado como par?etro
void Sound_Stop(struct T_SOUND *sonido) ;

//! Reinicia la reproducci? del sonido pasado como par?etro
void Sound_Restart(struct T_SOUND *sonido) ;

//! Borra el sonido pasado como par?etro y libera los recursos que haya podido alojar
void Sound_Delete(struct T_SOUND *sonido) ;

/*
class Sound {
};*/
