#ifndef ASSIGNATURA_H
#define ASSIGNATURA_H
#include "estudiant.h"
#include "professor.h"

const int MAX_ESTUDIANTS = 50;

class Assignatura
{
public:
    Assignatura() : m_nom(""), m_nEstudiants(0) {}
    Assignatura(const string& nom) : m_nom(nom), m_nEstudiants(0) {}

    void afegeixEstudiant(const string& nom, const string& niu);
    bool afegeixNota(const string& niu, float nota);
    float calculaNotaMitjana(const string& niu);
    string getNom() { return m_nom; }
private:
    string m_nom;
    Estudiant m_estudiants[MAX_ESTUDIANTS];
    int m_nEstudiants;
    Professor* m_professor;

    int cercaEstudiant(const string& niu);
};

#endif