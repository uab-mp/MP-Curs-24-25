#include "estudiant.h"

void Estudiant::inicialitza(string nom, string niu)
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

float Estudiant::calculaNotaMitjana()
{
    float mitjana = -1.0;
    float suma = 0.0;
    for (int i = 0; i < m_nNotes; i++)
        suma += m_notes[i];
    if (m_nNotes > 0)
        mitjana = suma / m_nNotes;
    return mitjana;
}