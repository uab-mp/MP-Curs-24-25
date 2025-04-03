#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
using namespace std;

class Professor
{
public:
    Professor() : m_nom(""), m_mail(""), m_despatx("") {}
    Professor(const string& nom, const string& mail, const string& despatx) :
        m_nom(nom), m_mail(mail), m_despatx(despatx) {}

    string getNom() { return m_nom; }
    string getMail() { return m_mail; }
    string getDespatx() { return m_despatx; }
private:
    string m_nom;
    string m_mail;
    string m_despatx;
};


#endif

