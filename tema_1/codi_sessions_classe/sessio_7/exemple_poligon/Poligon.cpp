#include "Poligon.h"

void Poligon::afegeixVertex(const Punt& pt)
{
	if (m_nVertexs < MAX_VERTEXS)
	{
		m_vertexs[m_nVertexs] = pt;
		m_nVertexs++;
		if (pt.getX() < m_topLeft.getX())
			m_topLeft.setX(pt.getX());
		else
			if (pt.getX() > m_bottomRight.getX())
				m_bottomRight.setX(pt.getX());
		if (pt.getY() < m_topLeft.getY())
			m_topLeft.setY(pt.getY());
		else
			if (pt.getY() > m_bottomRight.getY())
				m_bottomRight.setY(pt.getY());
	}	
}

float Poligon::calculaPerimetre() const
{
	float perimetre = 0;
	for (int i = 0; i < m_nVertexs - 1; i++)
		perimetre += m_vertexs[i].distancia(m_vertexs[i + 1]);
	perimetre += m_vertexs[0].distancia(m_vertexs[m_nVertexs-1]);
	return perimetre;
}