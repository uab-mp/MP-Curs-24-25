#ifndef COMANDA_H
#define COMANDA_H
#include "producte_comanda.h"
#include <string>

using namespace std;

class Comanda
{
public:
	Comanda();
	Comanda(const string &nomClient, const string &data, int totalProductes);
	Comanda(const Comanda &c);
	~Comanda();
	Comanda& operator=(const Comanda &c);
	string getClient() const { return m_nomClient; }
	string getData() const { return m_data; }
	float getImport() const { return m_importTotal; }
	void afegeixProducte(const string &codiProducte, int nUnitats, float preuUnitari);
	bool consultaProducte(const string &codiProducte, int &nUnitats, float &preuUnitari);
	bool eliminaProducte(const string &codiProducte);
private:
	string m_nomClient;
	string m_data;
	float m_importTotal;
	ProducteComanda* m_productes;
	int m_nProductes;
	int m_maxProductes;
};
#endif