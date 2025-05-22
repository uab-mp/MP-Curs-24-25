#ifndef EMPRESA_H
#define EMPRESA_H
#include "comanda.h"
#include "producte.h"
#include "node_comanda.h"
#include <vector>
using namespace std;

class Empresa
{
public:
	Empresa();
	~Empresa();
	void llegeixProductes(const string& nomFitxer);
	bool afegeixComanda(const string& nomFitxer);
	bool eliminaComanda(const string& nomClient, const string& data);
	bool importComanda(const string& nomClient, const string& data, float &import);
	bool DetallProducteComanda(const string& nomClient, const string& data, const string&codiProducte,
									int& nUnitats, float& preu);
private:
	NodeComanda* m_comandes;
	vector<Producte> m_productes;

};

#endif