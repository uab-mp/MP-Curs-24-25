#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif

#include "keyboard_sdl.h"

struct T_KEYBOARD
{
  int cnt[NUM_KEYBOARD_KEY_CODES] ;              // Indica si la tecla est?f?icamente pulsada
  int trg[NUM_KEYBOARD_KEY_CODES] ;              // Indica si la tecla ha sido pulsada este frame
};

void Keyboard_ProcessKeyDown(int tecla) ;
void Keyboard_ProcessKeyUp(int tecla) ;
void Keyboard_Init() ;
void Keyboard_Tick() ;

int Keyboard_GetKeyCnt(int cual) ;
int Keyboard_GetKeyTrg(int cual) ;
