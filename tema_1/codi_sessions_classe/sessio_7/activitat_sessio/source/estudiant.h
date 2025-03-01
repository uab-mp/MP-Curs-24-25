#ifndef ESTUDIANT_H
#define ESTUDIANT_H
#include <string>
using namespace std;

const int MAX_NOTES = 5;

class Estudiant
{
public:
    // Afegir constructors

    string getNom() { return m_nom; }
    string getNiu() { return m_niu; }
    void inicialitza(string nom, string niu);
    bool afegeixNota(float nota);
    float calculaNotaMitjana();
private:
    string m_nom;
    string m_niu;
    float m_notes[MAX_NOTES];
    int m_nNotes;
};


#endif


