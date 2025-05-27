#ifndef VECTOR_H
#define VECTOR_H

#include "punt.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class Vector
{
public:
	Vector();
	Vector(const Vector& v);
	~Vector();
	Vector& operator=(const Vector& v);
	bool insereix(const Punt& pt, int posicio);
	bool elimina(int posicio);
	int getNElements();
	int getMaxElements();
	Punt& operator[] (int posicio);
private:
	static const int TAMANY_MINIM = 5;
	Punt *m_array;
	int m_nElements;
	int m_maxElements;
	Punt m_valorDefecte;

};

#endif
