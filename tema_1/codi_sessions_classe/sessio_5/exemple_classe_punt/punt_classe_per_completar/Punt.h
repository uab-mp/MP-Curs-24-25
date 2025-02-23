#ifndef PUNT_H
#define PUNT_H

class Punt
{
public:
	void llegeix();
	void mostra();
	float distancia(Punt& p);

	float m_x, m_y;
};

#endif