#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "llibre.h"

const int MAX_LLIBRES = 100;

class Biblioteca
{
public:
	Biblioteca();
	int prestaLlibre(const string& titol, int& codiExemplar);
	int retornaLlibre(const string& titol, int codiExemplar);
	void afegeixLlibre(const Llibre& llibre);
private:
};

#endif