#include <iostream>
#include "Punt.h"

using namespace std;

int main()
{
	Punt p1 = { 0, 0 };
	Punt p2;

	p2.llegeix();
	float distancia = p1.distancia(p2);
	Punt p3;
	p3 = p1.suma(p2);

	cout << "Primer punt: ";
	p1.mostra();
	cout << endl;
	cout << "Segon punt: ";
	p2.mostra();
	cout << endl;
	cout << "Distancia: " << distancia << endl;
	cout << "Suma: ";
	p3.mostra();
	cout << endl;

	return 0;
}
