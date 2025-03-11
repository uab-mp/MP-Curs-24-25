#include "complex.h"
#include <iostream>

using namespace std;

int main()
{
	Complex c1, c2, resultat;
	char operacio;

	cout << "Introdueix operacio (1. suma, 2. resta, 3. multiplica, 4. sortir): ";
	cin >> operacio;
	while (operacio != '4')
	{
		// c1.llegeix();
		cin >> c1;
		// c2.llegeix();
		cin >> c2;
		switch (operacio)
		{
		case '1':
			// resultat = c1.suma(c2);
			resultat = c1 + c2;
			break;
		case '2':
			//resultat = c1.resta(c2);
			resultat = c1 - c2;
			break;
		case '3':
			// resultat = c1.multiplica(c2);
			resultat = c1 * c2;
			break;
		}
		// resultat.mostra();
		cout << resultat;
		cout << endl;
	}

	return 0;
}