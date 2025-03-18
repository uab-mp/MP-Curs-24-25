#include <fstream>
#include <iostream>

using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

void stringToPosicio(const string& posicio, int& fila, int& columna)
{
    fila = (N_FILES - 1) - (posicio[1] - '1');
    columna = posicio[0] - 'a';
}

void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, int& fila, int& columna)
{
    ifstream fitxer;
	fitxer.open(nomFitxer);
    string posicio;
    fitxer >> tipusFitxa >> posicio;
    stringToPosicio(posicio, fila, columna);
    fitxer.close();
}

void posicioToString(const int fila, const int columna, string& posicio)
{
    posicio = "a1";
    posicio[0] = 'a' + columna;
    posicio[1] = '1' + (N_FILES - 1) - fila;
}

void escriuFitxa(const string& nomFitxer, char tipusFitxa, int fila, int columna)
{
    ofstream fitxer;
	fitxer.open(nomFitxer);
    string posicio;
    posicioToString(fila, columna, posicio);
    fitxer << tipusFitxa << ' ' << posicio;
    fitxer.close();
}

int main()
{
    char tauler[N_FILES][N_COLUMNES];

    const string nomFitxerEntrada = "dames_input.txt";
    char tipusFitxa;
    int fila, columna;
    llegeixFitxa(nomFitxerEntrada, tipusFitxa, fila, columna);

    tauler[fila][columna] = tipusFitxa;
    cout << "Fitxa: " << tauler[fila][columna] << " a la posicio: " << fila << " " << columna << " del tauler" << endl;

    const string nomFitxerSortida = "dames_output.txt";
    escriuFitxa(nomFitxerSortida, tipusFitxa, fila, columna);
}