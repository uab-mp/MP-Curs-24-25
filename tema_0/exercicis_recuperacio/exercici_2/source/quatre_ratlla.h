#ifndef QUATRE_RATLLA_H
#define QUATRE_RATLLA_H

const int N_FILES = 6;
const int N_COLUMNES = 7;

int posaFitxa(int tauler[N_FILES][N_COLUMNES], int columna, int jugador);
bool quatreRatlla(int tauler[N_FILES][N_COLUMNES], int fila, int columna);
int jugaQuatreRatlla(int tauler[N_FILES][N_COLUMNES]);

#endif
