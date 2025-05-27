#ifndef JOC_H
#define JOC_H

#include "carta.h"
#include "jugador.h"
#include "moviment.h"




const int N_CARTES_JUGADOR = 7;

class Joc
{
public:
	Joc(): m_torn(-1), m_sentitTorn(1), m_nJugadors(0) {};
	~Joc() {};

	void inicialitza(const string& nomFitxer, int nJugadors);
	void fesMoviment();
	bool final();
	void guarda(const string& nomFitxer);
private:
	// PER COMPLETAR
	// Declarar els atributs del tipus més convenient utilitzant alguna de les classes
	// de la llibreria: vector, forward_list, list, stack, queue
	m_jugadors;
	m_cartesJugades;
	m_cartesBaralla;
	m_moviments;
	int m_nJugadors;
	int m_torn;
	int m_sentitTorn;
	
	void canviTorn();
	bool agafaCarta(Carta& carta, bool guardaMoviment);
	void tiraCarta();
};

#endif