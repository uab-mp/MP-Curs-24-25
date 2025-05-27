#include "llista_doble.h"

LlistaDoble::LlistaDoble()
{
     m_primer = NULL;
	 m_ultim = NULL;
}

LlistaDoble::~LlistaDoble()
{
	while (m_primer != NULL)
		m_primer = erase(m_primer);
}

bool LlistaDoble::empty() const
{
    return (m_primer == NULL);
}

Node* LlistaDoble::begin() const
{
    return m_primer;
}

Node* LlistaDoble::rbegin() const
{
	return m_ultim;
}

Node* LlistaDoble::insert(const int& valor, Node* posicio)
{

}

Node* LlistaDoble::erase(Node *posicio)
{

}

void LlistaDoble::unique()
{

}



LlistaDoble& LlistaDoble::operator=(const LlistaDoble& llista)
{

}