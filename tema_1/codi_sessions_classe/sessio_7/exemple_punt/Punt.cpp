#include "Punt.h"
#include <iostream>
#include <math.h>
using namespace std;


Punt::Punt(float x, float y)
{
	m_x = x;
	m_y = y;
}

void Punt::llegeix()
{
    cout << "Introdueix coordenades x i y del punt: ";
    cin >> m_x >> m_y;
}

void Punt::mostra()
{
    cout << "(" << m_x << ", " << m_y << ")";
}

Punt Punt::suma(Punt& p)
{
    Punt suma;
    suma.m_x = m_x + p.m_x;
    suma.m_y = m_y + p.m_y;
    return suma;
}


