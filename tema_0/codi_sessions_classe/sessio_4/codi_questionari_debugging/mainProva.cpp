#include "poligon.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	Poligon pol;

	// Aquestes instruccions son per llegir les dades del polígon del fitxer 'poligon.txt'
	// No s'han de tocar
	ifstream fitxerTest;
	fitxerTest.open("poligon.txt");
	streambuf* buffer_cin = cin.rdbuf(fitxerTest.rdbuf());

	llegeixPoligon(pol);
	
	// Aquestes instruccions son per llegir les dades del polígon del fitxer 'poligon.txt'
	// No s'han de tocar
	cin.rdbuf(buffer_cin);
	fitxerTest.close(); 
	
	float perimetre = calculaPerimetre(pol);
	cout << "Perimetre: " << perimetre << endl;

	Punt superiorEsquerra;
	Punt inferiorDreta;
	rectangleMinim(pol, superiorEsquerra, inferiorDreta);
	cout << "Cantonada superior esquerra: (" << superiorEsquerra.x << ", " << superiorEsquerra.y << ")" << endl;
	cout << "Cantonada inferior dreta: (" << inferiorDreta.x << ", " << inferiorDreta.y << ")" << endl;

	return 0;
}