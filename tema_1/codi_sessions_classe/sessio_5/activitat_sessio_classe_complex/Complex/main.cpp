
#include <iostream>
#include "complex.h"

using namespace std;

bool validaResSuma(Complex resultat, Complex c1, Complex c2)
{
	float realC1, imgC1, realC2, imgC2, realRes, imgRes;
	c1.recupera(realC1, imgC1);
	c2.recupera(realC2, imgC2);
	resultat.recupera(realRes, imgRes);
	if (realRes == (realC1 + realC2))
		if (imgRes == (imgC1 + imgC2))
			return true;
	return false;
}

bool validaResResta(Complex resultat, Complex c1, Complex c2)
{
	float realC1, imgC1, realC2, imgC2, realRes, imgRes;
	c1.recupera(realC1, imgC1);
	c2.recupera(realC2, imgC2);
	resultat.recupera(realRes, imgRes);
	if (realRes == (realC1 - realC2))
		if (imgRes == (imgC1 - imgC2))
			return true;
	return false;
}

bool validaResMultiplica(Complex resultat, Complex c1, Complex c2)
{
	float realC1, imgC1, realC2, imgC2, realRes, imgRes;
	c1.recupera(realC1, imgC1);
	c2.recupera(realC2, imgC2);
	resultat.recupera(realRes, imgRes);
	if (realRes == ((realC1 * realC2) - (imgC1 * imgC2)))
		if (imgRes == ((realC1 * imgC2) + (imgC1 * realC2)))
			return true;
	return false;
}

int main()
{
	float grade = 0.0;
	bool valid = true;
	Complex c1, c2, resultat;
	char operacio;

	cout << "Grade :=>> " << grade << endl;

	cout << "==================================================================" << endl;
	cout << "EXERCICI NOMBRES COMPLEXOS                                        " << endl;
	cout << "==================================================================" << endl;

	operacio = '1';
	cout << "==================================================================" << endl;
	cout << "Avaluar operacio SUMA:                                            " << endl;
	cout << "==================================================================" << endl;
	c1.inicialitza(1, 2);
	cout << "Nombre complex  C1: ";
	c1.mostra();
	cout << endl;
	c2.inicialitza(3, 4);
	cout << "Nombre complex  C2 : ";
	c2.mostra();
	cout << endl;
	resultat = avaluaOperacio(operacio, c1, c2);
	cout << "--------" << endl;
	cout << "Resultat operacio Suma: ";
	resultat.mostra();
	cout << endl;
	cout << "--------" << endl;
	bool validacio=validaResSuma(resultat, c1, c2);
	if (validacio) {
		cout << "RESULTAT OPERACIO SUMA CORRECTE" << endl;
		grade += 3.3;
	}
	else
	{
		cout << "ERROR OPERACIO SUMA" << endl;
		valid = false;
	}

	cout << "Grade :=>> " << grade << endl;

    operacio = '2';
    cout << "==================================================================" << endl;
    cout << "Avaluar operacio RESTA:                                           " << endl;
    cout << "==================================================================" << endl;
	c1.inicialitza(1, 2);
	cout << "Nombre complex  C1: ";
	c1.mostra();
	cout << endl;
	c2.inicialitza(3, 4);
	cout << "Nombre complex  C2: ";
	c2.mostra();
	cout << endl;
    resultat = avaluaOperacio(operacio, c1, c2);
	cout << "--------" << endl;
	cout << "Resultat operacio RESTA: ";
	resultat.mostra();
	cout << endl;
	validacio = validaResResta(resultat, c1, c2);
	cout << "--------" << endl;
	if (validacio) {
       cout << "RESULTAT OPERACIO RESTA CORRECTE" << endl;
	   grade += 3.3;
    }
    else
    {
       cout << "ERROR OPERACIO RESTA" << endl;
	   valid = false;
    }

	cout << "Grade :=>> " << grade << endl;

	operacio = '3';
	cout << "==================================================================" << endl;
	cout << "Avaluar operacio MULTIPLICA:                                      " << endl;
	cout << "==================================================================" << endl;
	c1.inicialitza(1, 2);
	cout << "Nombre complex  C1: ";
	c1.mostra();
	cout << endl;
	c2.inicialitza(3, 4);
	cout << "Nombre complex  C2: ";
	c2.mostra();
	cout << endl;
	resultat = avaluaOperacio(operacio, c1, c2);
	cout << "--------" << endl;
	cout << "Resultat operacio MULTIPLICA                                      " << endl;
	resultat.mostra();
	cout << endl;
	validacio = validaResMultiplica(resultat, c1, c2);
	cout << "--------" << endl;
	if (validacio)
	{
		cout << "RESULTAT OPERACIO MULTIPLICA CORRECTE" << endl;
		grade += 3.3;
	}
	else
	{
		cout << "ERROR OPERACIO MULTIPLICA" << endl;
		valid = false;
	}

	cout << "==================================================================" << endl;
	if (valid)
		cout << "Final del test sense errors" << endl;

	if (grade > 9)
		grade = 10;

	cout << "" << endl << "Grade :=>> " << grade << endl;

	return 0;
}