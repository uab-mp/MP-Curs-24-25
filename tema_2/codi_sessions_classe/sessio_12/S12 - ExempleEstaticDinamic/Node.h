#include <stdlib.h>
#include "Estudiant.h"

class Node
{
public:
	Node() {m_next = nullptr;};
	~Node() {};
	Node(const Estudiant& valor) {m_valor = valor; m_next = nullptr;}
    Node* getNext() { return m_next; }
    void setNext(Node* next) { m_next = next; }
    Estudiant getValor() { return m_valor; }
    void setValor(const Estudiant& valor) { m_valor = valor; }
private:
    Estudiant m_valor;
    Node* m_next;
};

