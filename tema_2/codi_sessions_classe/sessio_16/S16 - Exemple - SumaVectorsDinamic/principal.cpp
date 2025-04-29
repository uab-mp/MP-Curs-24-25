#include <iostream>
using namespace std;

const int MAX = 5;

void sumaVectors(int* p1, int* p2, int* pSuma, int nElements)
{
	for (int i = 0; i < nElements; i++)
		pSuma[i] = p1[i] + p2[i];
}

void llegeixVector(int *v, int nElements)
{
	for (int i = 0; i < nElements; i++)
	{
		cout << "Introdueix valor " <<
			i + 1 << " del vector: ";
		cin >> *(v + i);
	}
}


void mostraVector(int* v, int nElements)
{
	for (int i = 0; i < nElements; i++)
	{
		cout << *v << " ";
		v++;
	}
	cout << endl;
}

int main()
{
	int *v1, *v2, *vSuma;
	int nElements;

	cout << "Quants elements han de tenir els vectors ? ";
	cin >> nElements;

	v1 = new int[nElements];
	v2 = new int[nElements];
	vSuma = new int[nElements];

	llegeixVector(v1, nElements);
	llegeixVector(v2, nElements);

	sumaVectors(v1, v2, vSuma, nElements);

	cout << "Suma dels vectors: ";
	mostraVector(vSuma, nElements);

	delete[] v1;
	delete[] v2;
	delete[] vSuma;

	return 0;
}

