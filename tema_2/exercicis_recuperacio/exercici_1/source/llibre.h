#ifndef LLIBRE_H
#define LLIBRE_H

#include "exemplar.h"
#include <string>
using namespace std;

class Llibre
{
public:
	Llibre();
	Llibre(const string& titol, const string& autor, int nExemplars); 
	Llibre(const Llibre& llibre);
	~Llibre();
	Llibre& operator=(const Llibre& llibre);
	void setTitol(const string &titol) { m_titol = titol; }
	void setAutor(const string &autor) { m_autor = autor; }
	string& getTitol() { return m_titol; }
	string& getAutor() { return m_autor; }
	int getNExemplars() { return m_nExemplars; }
	Prestec* getPrestecExemplar(int codiExemplar) const;

	bool presta(const string&nom, const string& data, int &codiExemplar);
	bool retorna(int codiExemplar);
private:
	string m_titol;
	string m_autor;
	int m_nExemplars;
	Exemplar* m_exemplars;
};

#endif
