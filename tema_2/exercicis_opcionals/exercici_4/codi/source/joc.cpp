#include "joc.h"
#include <fstream>
using namespace std;

void Joc::inicialitza(const string& nomFitxer, int nJugadors)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int color, valor;
		fitxer >> color >> valor;
		while (!fitxer.eof())
		{
			// Llegeix els valors d'una carta del fitxer i els guarda en un objecte de tipus Carta
			Carta carta(color, valor);

			// PER COMPLETAR
			// Afegir la carta a m_cartesBaralla


			fitxer >> color >> valor;
		}
		fitxer.close();
		for (int i = 0; i < nJugadors; i++)
		{
			// Crea un objecte de tipus Jugador i l'inicialitza les cartes inicials del jugador
			Jugador jugador;
			for (int j = 0; j < N_CARTES_JUGADOR; j++)
			{	
				Carta carta;
				agafaCarta(carta, false);
				jugador.afegeixCarta(carta);
			}
			// PER COMPLETAR
			// Afegir el jugador a m_jugadors


			m_nJugadors++;
		}
		// Agafa la primera carta de la baralla de cartes
		Carta primeraCarta;
		agafaCarta(primeraCarta, false);
		// PER COMPLETAR
		// Afegir primeraCarta a m_cartesJugades


		m_torn = 0;
	}
}

bool Joc::agafaCarta(Carta& carta, bool guardaMoviment)
{

	// Aquest mètode es cridarà cada cop que un jugador hagi de robar una carta de la baralla.
	// Ha de treure una carta de la baralla i retornar-la al paràmetre per referència carta.
	// Si la baralla està buida ha de retornar false, i true en cas contrari.
	// A més a més, si el paràmetre guardaMoviment està a true s’ha de guardar la informació 
	// del moviment que s’ha fet(nº de jugador, ROBA_CARTA i el valor de la carta) 
	// a l’estructura que guarda tots els moviments de la partida.



}

void Joc::fesMoviment()
{
	// PER COMPLETAR
	// Recuperar a carta l'última carta afegida a m_cartesJugades
	Carta carta = ;
	Carta cartaRobar;
	// Executa l'acció associada a l'última carta robada
	switch (carta.getValor())
	{
	case CANVI_TORN:
		m_sentitTorn = -m_sentitTorn;
		canviTorn();
		canviTorn();
		break;
	case SALTA_TORN:
		canviTorn();
		break;
	case ROBA_DOS:
		if (agafaCarta(cartaRobar, true))
		{
			m_jugadors[m_torn].afegeixCarta(cartaRobar);
			if (agafaCarta(cartaRobar, true))
			{
				m_jugadors[m_torn].afegeixCarta(cartaRobar);
			}
		}
		break;
	}
	tiraCarta();
	canviTorn();
}

void Joc::tiraCarta()
{
	// Aquest mètode es cridarà quan un jugador hagi de tirar una carta.
	// Ha de cridar al mètode tiraCarta del jugador que té el torn.
	// Si el jugador no té cap carta per tirar ha de robar una carta de la baralla, 
	// afegir-la a les cartes del jugador i tornar a intentar tirar una carta, 
	// repetint fins que o bé pugui tirar carta o ja no quedin cartes per robar.
	// Ha de guardar tots els moviments que es facin(tant els de robar com els de tirar carta).




}

bool Joc::final()
{

	// Determina si s’ha arribat al final de la partida.
	// Hi ha dos casos en què s’arriba al final de la partida: 
	// si algun jugador es queda sense cartes 
	// o si cap dels jugadors ha pogut tirar en el seu últim torn de joc.



}

void Joc::guarda(const string& nomFitxer)
{

	// Guarda tots els moviments que s’han guardat en el fitxer que es passa com a paràmetre, 
	// seguint l’ordre en què s’han anat fent durant la partida.
	// Cada moviment ha d’estar en una línia diferent del fitxer amb el nº de jugador, 
	// el codi del moviment(robar o tirar), el color de la carta i el valor de la carta, 
	// separats per espais en blanc.




}

void Joc::canviTorn()
{
	m_torn += m_sentitTorn;
	if (m_torn < 0)
		m_torn = m_nJugadors - 1;
	if (m_torn >= m_nJugadors)
		m_torn = 0;
}
