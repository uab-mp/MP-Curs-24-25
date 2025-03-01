#ifndef ASSIGNATURA_H
#define ASSIGNATURA_H
#include "estudiant.h"
#include "professor.h"

const int MAX_ESTUDIANTS = 50;

class Assignatura
{
public:
    Assignatura(); 
    Assignatura(string nom); 
    Assignatura(string nom, string nomProfessor, string mailProfessor, string despatx, 
        int nEstudiants, string estudiants[MAX_ESTUDIANTS][2]);

    void afegeixEstudiant(string nom, string niu);
    bool afegeixNota(string niu, float nota);
    float calculaNotaMitjana(string niu);
    string getNomProfessor(); 
    string getMailProfessor(); 
    string getDespatxProfessor();
private:

};

#endif