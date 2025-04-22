#ifndef	PASSATGER_H
#define PASSATGER_H

#include <string>
using namespace std;

class Passatger
{
public:
	Passatger() {}
	Passatger(const string& dni, const string& nom) : m_dni(dni), m_nom(nom) {}
	void setDni(const string& dni) { m_dni = dni; }
	void setNom(const string& nom) { m_nom = nom; }
	const string& getDni() const { return m_dni; }
	const string& getNom() const { return m_nom; }
private:
	string m_dni;
	string m_nom;
};

#endif
