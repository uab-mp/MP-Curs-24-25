#ifndef POSICIO_H
#define POSICIO_H

#include <string>
#include <fstream>
using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Posicio
{
public:
    Posicio();
    Posicio(int fila, int columna);
    int getFila() const; 
    int getColumna() const; 
    string toString() const;
    void fromString(const string& pos);
private:
    int m_fila, m_columna;
};

ifstream& operator>>(ifstream& fitxer, Posicio& posicio);
ofstream& operator<<(ofstream& fitxer, const Posicio& posicio);

#endif // POSICIO_H
