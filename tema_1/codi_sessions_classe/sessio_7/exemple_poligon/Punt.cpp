#include "Punt.h"
#include <iostream>
#include <math.h>
using namespace std;


void Punt::llegeix()
{
	cout << "Introdueix coordinades x i y del punt: ";
	cin >> m_x >> m_y;
}

void Punt::mostra() const
{
	cout << "(" << m_x << ", " << m_y << ")";
}

float Punt::distancia(const Punt &p) const
{
	float dx = m_x - p.m_x;
	float dy = m_y - p.m_y;
	return sqrt(dx*dx + dy * dy);
}

