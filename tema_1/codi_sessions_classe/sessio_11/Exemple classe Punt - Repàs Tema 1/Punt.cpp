#include "Punt.h"
#include <iostream>
#include <math.h>
using namespace std;


void Punt::inicialitza(float x, float y)
{
	m_x = x;
	m_y = y;
}

istream &operator>>(istream &input, Punt &p)
{
	float x, y;
	input >> x >> y;
	p.inicialitza(x,y);
	return input;
}

ostream &operator<<(ostream &output, const Punt &p)
{
	output << "(" << p.getX() << ", " << p.getY() << ")";
	return output;
}

ifstream &operator>>(ifstream &input, Punt &p)
{
	float x, y;
	input >> x >> y;
	p.inicialitza(x, y);
	return input;
}

ofstream &operator<<(ofstream &output, const Punt &p)
{
	output << "(" << p.getX() << " " << p.getY() << ")";
	return output;
}

float Punt::operator-(const Punt &p) const
{
	float dx = m_x - p.m_x;
	float dy = m_y - p.m_y;
	return sqrt(dx*dx + dy * dy);
}

Punt Punt::operator+(const Punt &p) const
{
	Punt aux;
	aux.m_x = m_x + p.m_x;
	aux.m_y = m_y + p.m_y;
	return aux;
}