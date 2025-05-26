#ifndef PRESTEC_H
#define PRESTEC_H

#include <string>
using namespace std;

class Prestec
{
public:
    Prestec(const string& nom, const string& dataPrestec)
        : m_nom(nom), m_dataPrestec(dataPrestec) {}

    string getNom() const { return m_nom; }
    string getDataPrestec() const { return m_dataPrestec; }
private:
    string m_nom;
    string m_dataPrestec;
};

#endif