#ifndef NODE_H
#define NODE_H
#include <stdlib.h>
#include "punt.h"

class Node
{
public:
	Node() {m_next = nullptr;};
	~Node() {};
	Node(const Punt& valor) {m_valor = valor; m_next = nullptr;}
    Node* getNext() { return m_next; }
    void setNext(Node* next) { m_next = next; }
    Punt getValor() { return m_valor; }
    void setValor(const Punt& valor) { m_valor = valor; }
private:
    Punt m_valor;
    Node* m_next;
};

#endif