#ifndef POLIGON_H
#define POLIGON_H

#include "punt.h"
const int MAX_COSTATS = 30;

typedef struct
{
	Punt vertexs[MAX_COSTATS];
	int nCostats;
} Poligon;


void llegeixPoligon(Poligon& p);
void mostraPoligon(Poligon& p);
float calculaPerimetre(Poligon& p);
void rectangleMinim(Poligon& p, Punt& superiorEsquerra, Punt& inferiorDreta);
bool interseccioRectangle(Poligon& p1, Poligon& p2);



#endif
