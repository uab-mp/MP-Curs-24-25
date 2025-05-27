#ifndef NODE_H
#define NODE_H
#include <stdlib.h>

class Node
{
    public:
        Node();
        ~Node();
        Node (const int& valor) : m_valor(valor), m_next(nullptr), m_prev( ) {}
        Node* getNext() { return m_next; }
        void setNext(Node* next) { m_next = next; }
		Node* getPrev() { return m_prev; }
		void setPrev(Node* prev) { m_prev = prev; }
		int getValor() { return m_valor; }
        void setValor(const int &valor) { m_valor = valor; }
    private:
        int m_valor;
        Node* m_next;
		Node* m_prev;
};
#endif