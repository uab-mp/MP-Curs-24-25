#ifndef BATALLA_NAVAL_H
#define BATALLA_NAVAL_H

const int N_FILES = 5;
const int N_COLUMNES = 5;

typedef enum
{
    ESTAT_NUL = 0,
    ESTAT_AIGUA,
    ESTAT_VAIXELL,
    ESTAT_TOCAT,
    ESTAT_ENFONSAT
} EstatTauler;

typedef enum
{
    HORIZONTAL,
    VERTICAL
} Direccio;

bool batallaNaval(EstatTauler taulerInicial[N_FILES][N_COLUMNES], int nIntents, EstatTauler taulerResultat[N_FILES][N_COLUMNES]);

#endif
