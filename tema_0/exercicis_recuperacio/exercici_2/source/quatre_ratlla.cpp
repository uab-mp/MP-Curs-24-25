#include <iostream>
#include "quatre_ratlla.h"

using namespace std;


int posaFitxa(int tauler[N_FILES][N_COLUMNES], int columna, int jugador)
{
 
}


bool quatreRatlla(int tauler[N_FILES][N_COLUMNES], int fila, int columna)
{
	bool ratlla = quatreRatllaDireccio(tauler, fila, columna, 1, 0);
	if (!ratlla)
		ratlla = quatreRatllaDireccio(tauler, fila, columna, 0, 1);
		if (!ratlla)
			ratlla = quatreRatllaDireccio(tauler, fila, columna, 1, 1);
			if (!ratlla)
				ratlla = quatreRatllaDireccio(tauler, fila, columna, -1, 1);
	return ratlla;
}



int jugaQuatreRatlla(int tauler[N_FILES][N_COLUMNES])
{

}