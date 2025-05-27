#ifndef PUNT_H
#define PUNT_H

class Punt
{
public:
	Punt() { m_x = 0; m_y = 0; };
	Punt(int x, int y) { m_x = x; m_y = y; };
	Punt(const Punt& p) { m_x = p.m_x; m_y = p.m_y; };
	void setX(float x) { m_x = x; };
	void setY(float y) { m_y = y; };
	float getX()const { return m_x; };
	float getY()const { return m_y; };	
	bool operator==(const Punt& p) { return ((m_y == p.m_y) && (m_x == p.m_x)); };
private:
	float m_x;
	float m_y;
};

#endif

