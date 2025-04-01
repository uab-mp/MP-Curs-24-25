#ifndef LLISTA_H
#define LLISTA_H

#include "estudiant.h"
#include <iostream>
#include <fstream>
using namespace std;

class Llista
{
public:
	Llista() : m_nElements(0) {}
	Llista(const Estudiant v[], int mida);

	int getNumElements() const { return m_nElements; }
	bool pertany(const Estudiant& element) const;
	int cerca(const string& niu) const;
	Estudiant getElement(int posicio) const;

	void setElement(int posicio, const Estudiant& estudiant);
	bool insereix(const Estudiant& element, int posicio);
	bool elimina(int posicio);
	bool operator+(const Estudiant &element);
	bool operator-(const Estudiant &element);

private:
	static const int MAX_ELEMENTS = 2000000;
	Estudiant m_elements[MAX_ELEMENTS];
	int m_nElements;
};


ostream& operator<<(ostream& output, const Llista& llista);
ofstream& operator<<(ofstream& output, const Llista& llista);
ifstream& operator>>(ifstream& input, Llista& llista);

#endif