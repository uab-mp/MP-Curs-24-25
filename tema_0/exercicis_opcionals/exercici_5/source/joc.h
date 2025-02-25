#ifndef JOC_H
#define JOC_H

#include "carta.h"
#include "jugador.h"

const int MAX_JUGADORS = 4;
const int N_CARTES_JUGADOR = 7;
const int MAX_MOVIMENTS = 40;

typedef enum
{
	TIRA_CARTA = 0,
	ROBA_CARTA,
	PASSA_TORN
} TipusMoviment;

typedef struct
{

} Joc;

void jugaPartida(int cartesInicials[MAX_CARTES][2], int nJugadors, int moviments[MAX_MOVIMENTS][4], int& nMoviments);

#endif







