#include "Punt.h"
#include <iostream>
using namespace std;

int main()
{
	Punt p1 = { 0, 0 };
	Punt p2;

	llegeixPunt(p2);

	float distancia = distanciaPunts(p1, p2);

	cout << "Primer punt: ";
	mostraPunt(p1);
	cout << endl;
	cout << "Segon punt: ";
	mostraPunt(p2);
	cout << endl;
	cout << "Distancia: " << distancia << endl;


	return 0;
}

