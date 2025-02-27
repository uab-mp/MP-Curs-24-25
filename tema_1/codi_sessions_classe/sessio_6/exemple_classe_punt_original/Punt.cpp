#pragma once
#include "Punt.h"
#include <cmath>
#include <iostream>
using namespace std;

void Punt::llegeix()
{
    cout << "Introdueix les coordenades del punt : ";
	cin >> m_x >> m_y;
}

void Punt::mostra()
{
	cout << "(" << m_x << ", " << m_y << ")";
}

float Punt::distancia(Punt &p)
{
    float distancia = (m_x * m_x) + (m_y * m_y);
    return sqrt(distancia);
}

Punt Punt::suma(Punt& p)
{
	Punt pSuma;
	pSuma.m_x = m_x + p.m_x;
	pSuma.m_y = m_y + p.m_y;
	return pSuma;
}
