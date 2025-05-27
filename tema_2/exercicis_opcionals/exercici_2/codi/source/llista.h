#ifndef LLISTA_H
#define LLISTA_H
#include "node.h"

class Llista
{
public:
	Llista() { m_primer = nullptr; }
	~Llista();
	Llista(const Llista& l);
	Llista& operator=(const Llista& l);
	Node* insereix(const Punt& pt, Node* posicio);
	Node* elimina(Node* posicio);
	int getNElements() const;
	Node* getInici() { return m_primer; }
	bool esBuida() const { return m_primer == nullptr; }
		
 private:
	Node* m_primer;
};

#endif