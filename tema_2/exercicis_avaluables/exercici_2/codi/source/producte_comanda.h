#ifndef PRODUCTE_COMANDA_H
#define PRODUCTE_COMANDA_H

#include <string>
using namespace std;

class ProducteComanda
{
public:
	ProducteComanda() { m_nUnitats = 0; }
	ProducteComanda(const string& codi, int nUnitats, float preu) : m_codi(codi), m_nUnitats(nUnitats), m_preuUnitat(preu) {}

	string getCodi() const { return m_codi; }
	int getNUnitats() const { return m_nUnitats; }
	float getPreu() const { return m_preuUnitat; }

private:
	string m_codi;
	int m_nUnitats;
	float m_preuUnitat;
};
#endif