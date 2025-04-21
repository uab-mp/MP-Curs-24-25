#ifndef TAULER_H
#define TAULER_H


#include "posicio.hpp"


class Tauler 
{

public:
    Tauler() {};
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    string toString() const;
private:
};


#endif 