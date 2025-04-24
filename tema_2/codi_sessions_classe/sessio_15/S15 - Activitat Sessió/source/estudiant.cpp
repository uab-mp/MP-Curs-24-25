#include "estudiant.h"

Estudiant::Estudiant(const string& niu, const string& nom, int nAssignatures)
{

}

Estudiant::~Estudiant()
{

}

Estudiant& Estudiant::operator=(const Estudiant& e)
{

}

void Estudiant::allibera()
{

}

void Estudiant::afegeixAssignatura(const string& assignatura)
{ 

}

string Estudiant::getAssignatura(int posicio) const
{
	if (m_assignatures != nullptr)
		return m_assignatures[posicio];
	else return "";
}


