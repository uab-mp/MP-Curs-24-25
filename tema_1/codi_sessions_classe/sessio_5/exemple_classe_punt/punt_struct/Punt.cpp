#include "punt.h"
#include <iostream>
#include <math.h>

using namespace std;

void llegeixPunt(Punt& p)
{
	cin >> p.x >> p.y;
}

void mostraPunt(Punt& p)
{
	cout << "(" << p.x << "," << p.y << ")";
}

float distanciaPunts(Punt& p1, Punt& p2)
{
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	return sqrt(pow(dx,2) + pow(dy,2));
}