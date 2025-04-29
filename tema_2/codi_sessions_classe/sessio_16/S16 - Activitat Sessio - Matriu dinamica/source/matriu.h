#ifndef MATRIU_H
#define MATRIU_H
#include <string>
using namespace std;

int** creaMatriu(int nFiles, int nColumnes);
void llegeixMatriu(int** m, int nFiles, int nColumnes, const string& nomFitxer);
void sumaMatrius(int** m1, int** m2, int** suma, int nFiles, int nColumnes);
void destrueixMatriu(int** m, int nFiles);

#endif
