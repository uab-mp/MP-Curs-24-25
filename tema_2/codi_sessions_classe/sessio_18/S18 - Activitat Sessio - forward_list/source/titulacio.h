#ifndef TITULACIO_H
#define TITULACIO_H
#include <forward_list>
#include "estudiant.h"

class Titulacio
{
public:
	Titulacio(): m_nom(""), m_nEstudiants(0) {}
	void llegeixEstudiants(const string& nomFitxer);
	void mostraEstudiants();
	void eliminaEstudiantsAny(int any);
private:
	string m_nom;
	std::forward_list<Estudiant> m_estudiants;
	int m_nEstudiants;
};
#endif