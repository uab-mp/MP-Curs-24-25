#include "Data.h"
#include <iostream>
using namespace std;

void Data::llegeix()
{
	int dia, mes, any;

	cout << "Entra el dia: ";
	cin >> m_dia;
	cout << "Entra el mes: ";
	cin >> m_mes;
	cout << "Entra l'any: ";
	cin >> m_any;
}

