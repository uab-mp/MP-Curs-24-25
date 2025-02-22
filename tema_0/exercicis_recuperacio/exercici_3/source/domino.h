#ifndef DOMINO_H
#define DOMINO_H

const int MAX_FITXES = 7;
const int MAX_JUGADORS = 4;


typedef struct
{
	int valor1;
	int valor2;
} Fitxa;



int jugaDomino(Fitxa fitxesInicials[MAX_FITXES * MAX_JUGADORS], Fitxa fitxesJugades[MAX_FITXES * MAX_JUGADORS * 2], int& nFitxesJugades);

#endif

