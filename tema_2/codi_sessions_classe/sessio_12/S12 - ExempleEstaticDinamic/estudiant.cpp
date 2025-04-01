#include "estudiant.h"
#include <iostream>
#include <fstream>

using namespace std;

void Estudiant::inicialitza(const string& nom, const string& niu)
{
    m_nom = nom;
    m_niu = niu;
    m_nNotes = 0;
}

bool Estudiant::afegeixNota(float nota)
{
    bool correcte = false;
    if (m_nNotes < MAX_NOTES)
    {
        m_notes[m_nNotes++] = nota;
        correcte = true;
    }
    return correcte;
}

float Estudiant::calculaNotaMitjana() const
{
    float mitjana = -1.0;
    float suma = 0.0;
    for (int i = 0; i < m_nNotes; i++)
        suma += m_notes[i];
    if (m_nNotes > 0)
        mitjana = suma / m_nNotes;
    return mitjana;
}

bool Estudiant::operator==(const Estudiant& estudiant) const
{
    return ((m_nom == estudiant.m_nom) && (m_niu == estudiant.m_niu));
}

ostream& operator<<(ostream& output, const Estudiant& estudiant)
{
    output << estudiant.getNom() << " " << estudiant.getNiu() << " " << estudiant.calculaNotaMitjana();
    return output;
 }

ofstream& operator<<(ofstream& output, const Estudiant& estudiant)
{
    output << estudiant.getNom() << " " << estudiant.getNiu() << " " << estudiant.calculaNotaMitjana();
    return output;
}

ifstream& operator>>(ifstream& input, Estudiant& estudiant)
{
    string niu, nom;
    int nNotes;
    input >> nom >> niu >> nNotes;
    estudiant.inicialitza(nom, niu);
    int nota;
    for (int i = 0; i < nNotes; i++)
    {
        input >> nota;
        estudiant.afegeixNota(nota);
    }
    return input;
}