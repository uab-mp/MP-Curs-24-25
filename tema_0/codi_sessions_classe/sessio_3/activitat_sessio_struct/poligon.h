#ifndef POLIGON_H
#define POLIGON_H

#include "punt.h"
const int MAX_COSTATS = 30;

typedef struct
{

} Poligon;


void llegeixPoligon(Poligon& p);
void mostraPoligon(Poligon& p);
float calculaPerimetre(Poligon& p);
void rectangleMinim(Poligon& p, Punt& superiorEsquerra, Punt& inferiorDreta);


#endif
