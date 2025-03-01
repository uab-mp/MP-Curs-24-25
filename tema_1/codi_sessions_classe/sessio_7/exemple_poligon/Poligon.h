#pragma once
#include "Punt.h"

const int MAX_VERTEXS = 30;
class Poligon
{
public:
	Poligon(): m_topLeft(1000, 1000), m_bottomRight(0,0) { m_nVertexs = 0; }
	~Poligon() {}
	void afegeixVertex(const Punt& pt);
	Punt getTopLeft() const { return m_topLeft; }
	Punt getBottomRight() const { return m_bottomRight; }
	float calculaPerimetre() const;
private:
	Punt m_vertexs[MAX_VERTEXS];
	int m_nVertexs;
	Punt m_topLeft;
	Punt m_bottomRight;
};
