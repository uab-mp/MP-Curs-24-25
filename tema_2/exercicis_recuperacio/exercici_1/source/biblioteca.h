#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "llibre.h"
#include <vector>

using namespace std;

const int MAX_LLIBRES = 100;

class Biblioteca
{
public:
	Biblioteca() : m_nLlibres(0) {}
	int prestaLlibre(const string& titol, const string& nom, const string& data, int& codiExemplar);
	int retornaLlibre(const string& titol, int codiExemplar);
	void afegeixLlibre(const Llibre& llibre);
private:
	vector<Llibre> m_llibres;
	int m_nLlibres;
};
#endif
