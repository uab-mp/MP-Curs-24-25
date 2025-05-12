#ifndef TITULACIO_H
#define TITULACIO_H

#include "node_estudiant.h"
const int MAX_ESTUDIANTS = 300;

class Titulacio
{
public:
	Titulacio(): m_nom(""), m_nEstudiants(0), m_estudiants(nullptr) {}
	Titulacio(const string& nom, int maxAssignatures): m_nom(nom), m_nEstudiants(0), m_estudiants(nullptr) {}
	void afegeixEstudiant(const string& niu, const string& nom);
	void eliminaPrimerEstudiant();
	bool eliminaEstudiant(const string& niu);
	void insereixEstudiant(const string& niu, const string& nom);
	bool consultaEstudiant(const string& niu, Estudiant& e);

	// Mètode necessari pel test
	NodeEstudiant* getPrimerEstudiant() const { return m_estudiants; }
private:
	string m_nom;
	NodeEstudiant* m_estudiants;
	int m_nEstudiants;
};

#endif