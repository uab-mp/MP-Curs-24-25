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

ifstream& operator>>(ifstream& input, Punt& pt)
{
	float x, y;
	input >> x >> y;
	pt.setX(x);
	pt.setY(y);
	return input;
}

ofstream& operator<<(ofstream& output, const Punt& pt)
{
	output << "(" << pt.getX() << ", " << pt.getY() << ")";
	return output;
}

