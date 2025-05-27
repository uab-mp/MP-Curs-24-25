#ifndef JUGADOR_H
#define JUGADOR_H

#include "carta.h"
using namespace std;

class Jugador
{
public:
	Jugador(): m_haPogutTirar(true) {}
	~Jugador() {}

	void afegeixCarta(const Carta& carta);
	bool tiraCarta(const Carta& cartaTirada, Carta& cartaATirar);
	int getNCartes() const { return m_cartes.size(); }
	bool potTirar() const { return m_haPogutTirar; }
private:
	// PER COMPLETAR
	// Declarar l'atribut del tipus més convenient utilitzant alguna de les classes
	// de la llibreria: vector, forward_list, list, stack, queue
	m_cartes;
	bool m_haPogutTirar;
};

#endif