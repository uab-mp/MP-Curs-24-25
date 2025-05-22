#ifndef PRODUCTE_H
#define PRODUCTE_H

#include <string>
using namespace std;

class Producte
{
public:
	Producte() {}
	Producte(const string& nom, const string& codi, float preu) : m_nom(nom), m_codi(codi), m_preu(preu) {}

	void setNom(const string& nom) { m_nom = nom; }
	void setCodi(const string& codi) { m_codi = codi; }
	void setPreu(float preu) { m_preu = preu; }
	string getNom() const { return m_nom; }
	string getCodi() const { return m_codi; }
	float getPreu() const { return m_preu; }
private:
	string m_nom;
	string m_codi;
	float m_preu;
};

#endif