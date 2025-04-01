#ifndef ESTUDIANT_H
#define ESTUDIANT_H
#include <string>
using namespace std;

const int MAX_NOTES = 5;

class Estudiant
{
public:
    Estudiant() : m_nom(""), m_niu(""), m_nNotes(0) {}
    Estudiant(const string& nom, const string& niu) : m_nom(nom), m_niu(niu), m_nNotes(0) {}
    void setNom(const string& nom) { m_nom = nom; }
    void setNiu(const string& niu) { m_niu = niu; }
    string getNom() const { return m_nom; } 
    string getNiu() const { return m_niu; } 
    void inicialitza(const string& nom, const string& niu);
    bool afegeixNota(float nota);
    float calculaNotaMitjana() const;
    bool operator==(const Estudiant& estudiant) const;
private:
    string m_nom;
    string m_niu;
    float m_notes[MAX_NOTES];
    int m_nNotes;
};

ostream& operator<<(ostream& output, const Estudiant& llista);
ofstream& operator<<(ofstream& output, const Estudiant& llista);
ifstream& operator>>(ifstream& input, Estudiant& llista);

#endif


