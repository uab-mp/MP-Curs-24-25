#include "estudiant.h"
#include <iostream>

Estudiant::Estudiant(const string& niu, const string& nom)
{
	m_NIU = niu;
	m_nom = nom;
}

Estudiant::~Estudiant()
{
}

void Estudiant::inicialitza(const string& niu, const string& nom)
{
	m_NIU = niu;
	m_nom = nom;
	m_assignatures.clear();
}

void Estudiant::allibera()
{
	m_assignatures.clear();
}

void Estudiant::afegeixAssignatura(const string& assignatura)
{
	m_assignatures.push_back(assignatura);
}

void Estudiant::insereixAssignatura(const string& assignatura)
{
	vector<string>::iterator actual = m_assignatures.begin();
	bool trobat = false;
	while (!trobat && (actual != m_assignatures.end()))
	{
		if (*actual > assignatura)
			trobat = true;
		else
			actual++;
	}
	m_assignatures.insert(actual, assignatura);
}

void Estudiant::eliminaAssignatura(const string& assignatura)
{
	vector<string>::iterator actual = m_assignatures.begin();
	bool trobat = false;
	while (!trobat && (actual != m_assignatures.end()))
	{
		if (*actual == assignatura)
			trobat = true;
		else
			actual++;
	}
	if (trobat)
		m_assignatures.erase(actual);
}

void Estudiant::mostraAssignatures()
{
/*	vector<string>::iterator actual;
	for (actual = m_assignatures.begin(); actual != m_assignatures.end(); actual++)
		cout << *actual << endl;
		*/
	for (int i = 0; i < m_assignatures.size(); i++)
		cout << m_assignatures[i] << endl;
}

string Estudiant::getAssignatura(int posicio) const
{
	if ((posicio >= 0) && (posicio < m_assignatures.size()))
		return m_assignatures[posicio];
	else return "";
}

