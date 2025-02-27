#include "Punt.h"
#include <iostream>
using namespace std;

int main()
{
	Punt p1;
	p1.llegeix();

	Punt p2;
	p2.llegeix();
	if (p1.getDimensio() == p2.getDimensio())
	{
		float distancia = p1.distancia(p2);
		Punt pSuma = p1.suma(p2);

		cout << "Primer punt: ";
		p1.mostra();
		cout << endl;
		cout << "Segon punt: ";
		p2.mostra();
		cout << endl;
		cout << "Distancia: " << distancia << endl;
		cout << "Suma: ";
		pSuma.mostra();
		cout << endl;
	}
	return 0;
}
