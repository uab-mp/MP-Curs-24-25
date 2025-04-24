#ifndef TITULACIO_H
#define TITULACIO_H
#include "estudiant.h"
const int MAX_ESTUDIANTS = 20;

class Titulacio
{
public:
	Titulacio() : m_nom(""), m_nEstudiants(0), m_nMaxAssignatures(0) {}
	Titulacio(const string& nom, int maxAssignatures) : m_nom(nom), m_nEstudiants(0), m_nMaxAssignatures(maxAssignatures) {}
	void afegeixEstudiant(const string& niu, const string& nom);
	bool eliminaEstudiant(const string& niu);
	bool consultaEstudiant(const string& niu , Estudiant& e);
private:
	string m_nom;
	int m_nMaxAssignatures;
	Estudiant m_estudiants[MAX_ESTUDIANTS];
	int m_nEstudiants;
};

#endif