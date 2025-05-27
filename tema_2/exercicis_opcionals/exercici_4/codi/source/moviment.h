#ifndef MOVIMENT_H
#define

#include "carta.h"

const int TIRA_CARTA = 0;
const int ROBA_CARTA = 1;

class Moviment
{
public:
	Moviment(int jugador, int accio, const Carta& carta) : m_jugador(jugador), m_accio(accio){ m_carta = carta; }
	int getJugador() const { return m_jugador; }
	int getAccio() const { return m_accio; }
	Carta getCarta() const { return m_carta; }
private:
	int m_jugador;
	int m_accio;
	Carta m_carta;
};

#endif 