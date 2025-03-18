#include <iostream>
#include "posicio.h"

using namespace std;


void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, Posicio& posicio)
{

}

void escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio)
{
 
}

int main()
{
    char tauler[N_FILES][N_COLUMNES];

    const string nomFitxerEntrada = "dames_input.txt";
    char tipusFitxa;
    Posicio posicio;
    llegeixFitxa(nomFitxerEntrada, tipusFitxa, posicio);

    int fila = posicio.getFila();
    int columna = posicio.getColumna();
    tauler[fila][columna] = tipusFitxa;
    cout << "Fitxa: " << tauler[fila][columna] << " a la posicio: " << fila << " " << columna << " del tauler" << endl;

    const string nomFitxerSortida = "dames_output.txt";
    escriuFitxa(nomFitxerSortida, tipusFitxa, posicio);
}