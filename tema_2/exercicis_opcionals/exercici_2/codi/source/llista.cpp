

#include "llista.h"

Llista::~Llista()
{
	while (m_primer != nullptr)
		elimina(nullptr);
}

Llista::Llista(const Llista& l)
{
	m_primer = nullptr;
	Node* aux = l.m_primer;
	Node* aux_nova = m_primer;
	while (aux != nullptr)
	{
		aux_nova = insereix(aux->getValor(), aux_nova);
		aux = aux->getNext();
	}

}

Llista& Llista::operator=(const Llista& l)
{

}

Node *Llista::insereix(const Punt& valor, Node *posicio)
{

}

Node *Llista::elimina(Node *posicio)
{
 
}

int Llista::getNElements() const
{
	int nElements = 0;
	Node *aux = m_primer;
	while (aux != NULL)
	{
		nElements++;
		aux = aux->getNext();
	}
	
	return nElements;
}

