#ifndef TAULER_H
#define TAULER_H
#include "casella.h"
#include <string>
using namespace std;

const int NUMERO_CASELLES = 63;
const int NUMERO_JUGADORS = 4;
class Tauler
{
public:
	Tauler();
	void inicialitza(int tipusCaselles[], int nCaselles, const int& nJugadors);
	void tornJoc(int valorDau);
	int getTipusCasella(int nCasella) const;
	void getEstatJugador(int nJugador, int& posicio, bool& potTirar, int& nTornsInactiu, bool& guanyador); 
private:

};

#endif