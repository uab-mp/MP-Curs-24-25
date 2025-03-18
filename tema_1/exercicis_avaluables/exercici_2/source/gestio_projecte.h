#ifndef GESTIO_PROJECTE_H
#define GESTIO_PROJECTE_H

#include <string>
#include "data.h"
#include "tasca.h"
using namespace std;

const int MAX_TASQUES = 100;

class GestioProjecte 
{
public:
    GestioProjecte(): m_nTasques(0) {} ;
    void afegeixTasca(const string& nom, int duradaPrevista, const Data& dataActual, int nParticipants, 
        string participants[MAX_PARTICIPANTS]);
    void endarrereixTasca(const string& nom, int nDies);
    int completaTasca(const string& nom, const Data& dataActual);
    void tasquesPendents(const string& nom, const Data& dataActual, int nDies, int& nTasques, string tasques[]);
    void retardTasques(const Data& dataActual, int& nPersones, string persones[]);
    void recuperaTasca(const string& nom, Data& dataPrevista, bool& completada, Data& dataFinal);
private:
    int m_nTasques;
    Tasca m_tasques[MAX_TASQUES];
};



#endif