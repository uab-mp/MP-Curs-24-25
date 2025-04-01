#include "Node.h"

class LlistaDinamica
{
public:
	LlistaDinamica() { m_primer = nullptr; }
	~LlistaDinamica();
	LlistaDinamica(const LlistaDinamica& l);
	LlistaDinamica& operator=(const LlistaDinamica& l);
	Node* insereix(const Estudiant& e, Node* posicio);
	Node* elimina(Node* posicio);
	int getNElements() const;
	Node* getInici() { return m_primer; }
	bool esBuida() const { return m_primer == nullptr; }
		
 private:
	Node* m_primer;
};
