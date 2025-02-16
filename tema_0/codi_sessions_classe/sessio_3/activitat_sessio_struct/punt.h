#ifndef PUNT_H
#define PUNT_H

typedef struct
{
	float x;
	float y;
} Punt;

void llegeixPunt(Punt& p);
void mostraPunt(Punt& p);
float distanciaPunts(Punt& p1, Punt& p2);

#endif