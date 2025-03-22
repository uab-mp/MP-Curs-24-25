#ifndef GESTIO_AULES_H
#define GESTIO_AULES_H

#include "aula.h"
#include "assignatura.h"

const int MAX_AULES = 10;
const int MAX_ASSIGNATURES = 100;

class GestioAules
{
public:
    GestioAules();
    void inicialitzaAules(const string& nomFitxer);
    void inicialitzaAssignatures(const string& nomFitxer);
    string assignaAula(const string& codiAssignatura);
    bool eliminaReserva(const string& codiAssignatura);
    string aulaAssignatura(const string& codiAssignatura);
    void assignaturesAula(const string& codiAula, int& nAssignatures, string assignatures[]);
    void reservesAula(const string& codiAula, const string& nomFitxer);
private:
 
};



#endif