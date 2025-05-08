#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <cassert>

#include "libreria.h"

#include "sound.h"
#include "stb_vorbis.h"


#define NUM_CANALES_STEREO                                       2
#define NO_SOUND_CHANNEL_AVAILABLE                               -1

#pragma warning(disable : 4996)

//#define DEBUG_TEST_TONE

#ifdef DEBUG_TEST_TONE
  float g_angulo_generador ;
#endif

signed short *g_music_buffer ;
//signed short *g_sound_buffer ;
signed short *g_sound_buffer_queue[MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS] ;

struct T_SOUND *g_current_music = NULL ;
//struct T_SOUND *g_current_sound = NULL ;

int g_samples ;


struct T_SOUND *g_Sound_Queue[MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS] ;

int g_CanalesLibres[MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS] ;
int g_Posicion_Pila_Sonidos_Libres ;


void Sound_Lock()
{
  SDL_LockAudio() ;
}

void Sound_Unlock()
{
  SDL_UnlockAudio() ;
}

void PushCanalLibre(int cual)
{
  assert(g_Posicion_Pila_Sonidos_Libres < (MAX_SIMULTANEOUS_SOUND_CHANNELS-1)) ;

  g_CanalesLibres[g_Posicion_Pila_Sonidos_Libres] = cual ;
  g_Sound_Queue[cual] = NULL ;

  g_Posicion_Pila_Sonidos_Libres++ ;
}

int PopCanalLibre()
{
  int canal_libre = NO_SOUND_CHANNEL_AVAILABLE ;

  if(g_Posicion_Pila_Sonidos_Libres > 0) {

    g_Posicion_Pila_Sonidos_Libres-- ;
    canal_libre = g_CanalesLibres[g_Posicion_Pila_Sonidos_Libres] ;
  }

  return canal_libre ;
}




// ------------------------------------------------------------------------------------------------
// Devuelve el tama? en bytes del fichero
//
int TamanyoFicheroAbierto(FILE *fichero)
{
  int posicion_actual, tamanyo ;

	posicion_actual = ftell(fichero) ;

  // Vamos al final del fichero

  fseek(fichero, 0, SEEK_END) ;
	tamanyo = ftell(fichero) ;

  // Volvemos a donde estuvi?emos

  fseek(fichero, posicion_actual, SEEK_SET) ;

  return tamanyo ;
}

// ------------------------------------------------------------------------------------------------
// Devuelve el tama? en bytes del fichero
int TamanyoFichero(char *ruta)
{
  FILE *fichero ;
  int tamanyo ;

  fichero = fopen(ruta, "rb") ;

  if(fichero == NULL) return 0 ;

  tamanyo = TamanyoFicheroAbierto(fichero) ;

  return tamanyo ;
}

int Sound_GetSoundQueueSlot(struct T_SOUND *sonido)
{
  sonido->posicion_cola = PopCanalLibre() ;

  // Si no tenemos un slot de reproducci? libre nos marchamos sin hacer nada

  if(sonido->posicion_cola == NO_SOUND_CHANNEL_AVAILABLE) {

    return NO_SOUND_CHANNEL_AVAILABLE ;
  }

  // Si tenemos un slot asignado nos metemos en la cola

  g_Sound_Queue[sonido->posicion_cola] = sonido ;

  return sonido->posicion_cola ;
}

void Sound_Callback(void *unused, Uint8 *stream, int len)
{
  int var1 ;
  int num_samples ;
  signed short *puntero ;
  int var_sonido ;
  int valor_final ;

  (void)unused ;

  assert(stream) ;

  Sound_Lock() ;


  num_samples = (len / NUM_CANALES_STEREO) ;

  //ASSERT((num_samples / NUM_CANALES_STEREO) <= g_samples) ;

  puntero = (signed short *)stream ;

  memset(g_music_buffer, 0, g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;

  if(g_current_music != NULL) {

    if(g_current_music->ogg != NULL) {

      /*if(g_current_music->buffer_fichero == NULL) g_current_music->posicion_stream = stb_vorbis_get_file_offset(g_current_music->ogg) ;
      else */g_current_music->posicion_stream = stb_vorbis_get_sample_offset(g_current_music->ogg) ;

      if(g_current_music->posicion_stream == g_current_music->num_samples) {

        if(g_current_music->bLoop) Sound_Restart(g_current_music) ;
        else Sound_Stop(g_current_music) ;
      }

      stb_vorbis_get_samples_short_interleaved(g_current_music->ogg, 2, g_music_buffer, num_samples) ;
    }
  }



  // Paso previo de render de .ogg

  for(var_sonido = 0; var_sonido < MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS; var_sonido++) {

    struct T_SOUND *sonido = g_Sound_Queue[var_sonido] ;

    // Borramos el contenido del buffer

    memset(g_sound_buffer_queue[var_sonido], 0, g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;

    // ?Hay sonido?

    if(sonido != NULL) {

      // ?Tiene un stream ogg?

      if(sonido->ogg != NULL) {

        if(sonido->buffer_fichero == NULL) sonido->posicion_stream = stb_vorbis_get_file_offset(sonido->ogg) ;
        else sonido->posicion_stream = stb_vorbis_get_sample_offset(sonido->ogg) ;

        if(sonido->posicion_stream == sonido->num_samples) {

          if(sonido->bLoop) Sound_Restart(sonido) ;
          else Sound_Stop(sonido) ;
        }

        if(sonido->estado == SOUND_STATE_PLAYING) {

          // Llenamos el contenido del buffer hasta donde podamos

          stb_vorbis_get_samples_short_interleaved(sonido->ogg, 2, g_sound_buffer_queue[var_sonido], num_samples) ;
        }
      }
    }
  }


  for(var1 = 0; var1 < num_samples; var1++) {

#ifdef DEBUG_TEST_TONE

    *puntero = 1000 * sin(g_angulo_generador) ;
    g_angulo_generador += 0.1f ;

#else

    valor_final = 0 ;

    for(var_sonido = 0; var_sonido < MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS; var_sonido++) {

      if(g_Sound_Queue[var_sonido] != NULL) {

         valor_final += g_sound_buffer_queue[var_sonido][var1] ;
      }
    }

    valor_final += g_music_buffer[var1] ;

    *puntero = (short)(valor_final / MAX_SIMULTANEOUS_SOUND_CHANNELS) ;
    //*puntero = g_music_buffer[var1] ;

#endif

    puntero++ ;

  }

  Sound_Unlock() ;
}

void Sound_Init()
{
  SDL_AudioSpec desired, obtained ;
  int resultado ;
  int var_sonido ;


  desired.format = AUDIO_S16 ;

  desired.freq = 44100 ;
  desired.samples = (Uint16) 512 ;

  desired.channels = 2 ;
  desired.callback = Sound_Callback ;

  desired.userdata = NULL ;

  resultado = SDL_OpenAudio(&desired, &obtained) ;

  g_samples = obtained.samples ;

  if ( resultado != 0 ) {

    if (resultado < 0)  {

      int a = 5 ;
      (void)a ;
    }
  }

  g_current_music = NULL ;
  g_music_buffer = (signed short *)malloc(g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;
  memset(g_music_buffer, 0, g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;

//  g_current_sound = NULL ;
  //g_sound_buffer = (signed short *)malloc(g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;
//  memset(g_sound_buffer, 0, g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;


  // Inicializamos la cola de reproducci? de sonidos

  g_Posicion_Pila_Sonidos_Libres = 0 ;

  for(var_sonido = 0; var_sonido < MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS; var_sonido++) {

    g_sound_buffer_queue[var_sonido] = (signed short *)malloc(g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;
    memset(g_sound_buffer_queue[var_sonido], 0, g_samples * NUM_CANALES_STEREO * sizeof(signed short)) ;

    PushCanalLibre(var_sonido) ;
  }


  SDL_PauseAudio(0) ;
}

struct T_SOUND *Sound_LoadFileStream(char *path, int bLoop)
{
  struct T_SOUND *new_sound ;
  int error ;

  new_sound = (struct T_SOUND *) malloc(sizeof(struct T_SOUND)) ;

  new_sound->bLoop = bLoop ;
  new_sound->posicion_stream = 0 ;

  new_sound->estado = SOUND_STATE_STOPPED ;
  new_sound->posicion_cola = -1 ;

  new_sound->buffer_fichero = NULL ;

  new_sound->ogg = stb_vorbis_open_filename(path, &error, NULL) ;

  if(new_sound->ogg == NULL) {

    printf("\nERROR: No se encuentra el archivo %s", path) ;
    new_sound->num_samples = 0 ;
  }
  else {

    // stb_vorbis_info info = stb_vorbis_get_info(new_sound->ogg) ;

    new_sound->num_samples = stb_vorbis_stream_length_in_samples(new_sound->ogg) ;
  }

  return new_sound ;
}

struct T_SOUND *Sound_LoadMemoryStream(char *path, int bLoop)
{
  struct T_SOUND *new_sound ;
  int tam_buffer ;
  int error ;
  FILE *fichero ;

  new_sound = (struct T_SOUND *) malloc(sizeof(struct T_SOUND)) ;

  new_sound->bLoop = bLoop ;
  new_sound->posicion_stream = 0 ;

  new_sound->estado = SOUND_STATE_STOPPED ;
  new_sound->posicion_cola = -1 ;

  fichero = fopen(path, "rb") ;

  if(fichero == NULL) {

    printf("\nERROR: No se encuentra el archivo %s", path) ;

    new_sound->buffer_fichero = NULL ;
    new_sound->ogg = NULL ;
    new_sound->num_samples = 0 ;
  }
  else {

    tam_buffer = TamanyoFicheroAbierto(fichero) ;

    new_sound->buffer_fichero = (unsigned char *) malloc(tam_buffer) ;
    fread(new_sound->buffer_fichero, tam_buffer, 1, fichero) ;

    fclose(fichero) ;

    new_sound->ogg = stb_vorbis_open_memory(new_sound->buffer_fichero, tam_buffer, &error, NULL) ;
    new_sound->num_samples = stb_vorbis_stream_length_in_samples(new_sound->ogg) ;
  }

  return new_sound ;
}


struct T_SOUND *Sound_LoadMusic(char *path, int bStream)
{
  if(bStream) g_current_music = Sound_LoadFileStream(path, PLAY_THEN_LOOP_AT_END) ;
  else g_current_music = Sound_LoadMemoryStream(path, PLAY_THEN_LOOP_AT_END) ;

  return g_current_music ;
}

struct T_SOUND *Sound_LoadSound(char *path)
{
  struct T_SOUND *sound ;

//  g_current_sound = Sound_LoadMemoryStream(path, PLAY_THEN_STOP_AT_END) ;
//  return g_current_sound ;

  sound = Sound_LoadMemoryStream(path, PLAY_THEN_STOP_AT_END) ;

  return sound ;
}


int Sound_Play(struct T_SOUND *sonido, int mode)
{
//  g_current_sound = sonido ;

  if(sonido->estado != SOUND_STATE_PLAYING) {

    // Si el sonido estaba parado pedimos una nueva posici? en la cola

    if(Sound_GetSoundQueueSlot(sonido) == NO_SOUND_CHANNEL_AVAILABLE) {

      return NO_SOUND_CHANNEL_AVAILABLE ;
    }

    // ?Comenzaremos desde el principio?

    if(sonido->estado != SOUND_STATE_PAUSED ||
       mode == SOUND_FORCE_RESTART) {

      // Reiniciar el sonido
      Sound_Restart(sonido) ;
    }

    // Cambiamos el estado a "playing"

    sonido->estado = SOUND_STATE_PLAYING ;
  }
  else {

    // Si el sonido no estaba playe?dose y no est?en pause hay que reiniciarlo

    if(mode != SOUND_DO_NOT_RESTART_IF_ALREADY_PLAYING) Sound_Restart(sonido) ;
  }

  // Devolvemos la posici? en la cola de reproducci?
  return sonido->posicion_cola ;
}

void Sound_FreeSoundQueueSlot(struct T_SOUND *sonido)
{
  // Si el sonido no est?reproduci?dose no hacemos nada

  if(sonido->posicion_cola == -1) return ;

  // Liberamos la posici? de la cola que est?ocupando el sonido

  PushCanalLibre(sonido->posicion_cola) ;
  sonido->posicion_cola = -1 ;
}

void Sound_Delete(struct T_SOUND *sonido)
{
  // Liberamos la posici? de la cola que est?ocupando el sonido

  Sound_FreeSoundQueueSlot(sonido) ;

  // Falta...
}

void Sound_Pause(struct T_SOUND *sonido)
{
  // Liberamos la posici? de la cola que est?ocupando el sonido

  Sound_FreeSoundQueueSlot(sonido) ;

  sonido->estado = SOUND_STATE_PAUSED ;
}

void Sound_Stop(struct T_SOUND *sonido)
{
  // Liberamos la posici? de la cola que est?ocupando el sonido

  Sound_FreeSoundQueueSlot(sonido) ;

  sonido->estado = SOUND_STATE_STOPPED ;
}

void Sound_Restart(struct T_SOUND *sonido)
{
  Sound_Lock() ;

  stb_vorbis_seek_start(sonido->ogg) ;
  sonido->posicion_stream = 0 ;

  Sound_Unlock() ;
}

