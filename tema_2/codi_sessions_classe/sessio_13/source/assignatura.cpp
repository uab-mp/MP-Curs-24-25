#include "assignatura.h"

void Assignatura::afegeixEstudiant(const string& nom, const string& niu)
{
    if (m_nEstudiants < MAX_ESTUDIANTS)
    {
        m_estudiants[m_nEstudiants++].inicialitza(nom, niu);
    }
}


int Assignatura::cercaEstudiant(const string& niu)
{
    bool trobat = false;
    int i = 0;
    while (!trobat && (i < m_nEstudiants))
    {
        if (m_estudiants[i].getNiu() == niu)
            trobat = true;
        else
            i++;
    }
    if (trobat)
        return i;
    else
        return -1;
}

bool Assignatura::afegeixNota(const string& niu, float nota)
{
    bool correcte;
    int pos = cercaEstudiant(niu);
    if (pos != -1)
        correcte = m_estudiants[pos].afegeixNota(nota);
    else
        correcte = false;
    return correcte;
}

float Assignatura::calculaNotaMitjana(const string& niu)
{
    float mitjana;
    int pos = cercaEstudiant(niu);
    if (pos != -1)
        mitjana = m_estudiants[pos].calculaNotaMitjana();
    else
        mitjana = -1.0;
    return mitjana;
}