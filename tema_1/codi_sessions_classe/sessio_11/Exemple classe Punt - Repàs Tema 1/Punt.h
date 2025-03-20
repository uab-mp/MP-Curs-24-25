#ifndef PUNT_H
#define PUNT_H

#include <iostream>
#include <fstream>
using namespace std;

class Punt
{
public:
	Punt(): m_x(0), m_y(0) {  }
	Punt(float x, float y) : m_x(x), m_y(y) {}
	~Punt() { }
	void inicialitza(float x, float y);
	float getX() const { return m_x; }
	float getY() const { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	float operator-(const Punt &p) const;
	Punt operator+(const Punt &p) const;
private:
	float m_x, m_y;
};

istream &operator>>(istream &input, Punt &p);
ostream &operator<<(ostream &output, const Punt &p);
ifstream &operator>>(ifstream &input, Punt &p);
ofstream &operator<<(ofstream &output, const Punt &p);

#endif