#ifndef PUNT_H
#define PUNT_H
#include <fstream>
using namespace std;

class Punt
{
public:
	Punt(): m_x(0), m_y(0) {  }
	Punt(float x, float y) : m_x(x), m_y(y) {}
	~Punt() { }
	float getX() const { return m_x; }
	float getY() const { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void llegeix();
	void mostra() const;
	float distancia(const Punt &p) const;
private:
	float m_x, m_y;
};

ifstream& operator>>(ifstream& input, Punt& pt);
ofstream& operator<<(ofstream& output, const Punt& pt);

#endif
