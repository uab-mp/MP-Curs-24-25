#include "Poligon.h"
#include "funcions_poligons.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void mostraBool(bool valor)
{
	if (valor)
		cout << "TRUE ";
	else
		cout << "FALSE ";
}

void llegeixDadesPoligon(Poligon& pol, const string& nomFitxer)
{
	fstream fitxerTest;

	int nVertexs;
	float x, y;
	fitxerTest.open(nomFitxer);
	cout << "Comment :=>> Afegint vertexs al poligon: ";
	fitxerTest >> x >> y;
	while (!fitxerTest.eof())
	{
		Punt pt(x, y);
		pol.afegeixVertex(pt);
		cout << "(" << x << ", " << y << ") ";
		fitxerTest >> x >> y;
	}
	cout << endl;
	fitxerTest.close();
	cout << "Comment :=>> -----" << endl;
}


float testCalculaPerimetre()
{
	const int N_PROVES = 4;
	float perimetreEsperat[N_PROVES] = { 12, 14, 12, 20 };

	float reduccio = 0.0;
	float perimetreObtingut;

	cout << endl << endl;
	cout << "Comment :=>> Iniciant test de la funcio CalculaPerimetre" << endl;
	cout << "Comment :=>> ===========================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		string nomFitxer;
		ifstream fitxerTest;
		Poligon pol;

		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Llegint dades del poligon...." << endl;
		nomFitxer = "poligon" + to_string(i + 1) + ".txt";
		llegeixDadesPoligon(pol, nomFitxer);

		perimetreObtingut = pol.calculaPerimetre();

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Perimetre esperat: " << perimetreEsperat[i] << endl;
		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Perimetre obtingut: " << perimetreObtingut << endl;
		if (perimetreEsperat[i] == perimetreObtingut)
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	if (reduccio > 4.0)
		reduccio = 4.0;
	return reduccio;
}

float testRectangleMinim()
{
	const int N_PROVES = 4;
	Punt superiorEsquerraEsperat[N_PROVES] = { {0, 0}, {1, 1}, {3, 3}, {4, 4} };
	Punt inferiorDretaEsperat[N_PROVES] = { {4, 3}, {4, 5}, {6, 6}, {10, 12} };


	float reduccio = 0.0;
	Punt superiorEsquerraObtingut, inferiorDretaObtingut;

	cout << endl << endl;
	cout << "Comment :=>> Iniciant test del calcul del RectangleMinim" << endl;
	cout << "Comment :=>> ===========================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		string nomFitxer;
		ifstream fitxerTest;
		Poligon pol;

		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Llegint dades del poligon...." << endl;
		nomFitxer = "poligon" + to_string(i + 1) + ".txt";
		llegeixDadesPoligon(pol, nomFitxer);

		superiorEsquerraObtingut = pol.getTopLeft();
		inferiorDretaObtingut = pol.getBottomRight();

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Punt superior esquerra esperat: " <<
			"(" << superiorEsquerraEsperat[i].getX() << ", " <<
			superiorEsquerraEsperat[i].getY() << ")" << endl;
		cout << "Comment :=>> Punt inferior dreta esperat: " <<
			"(" << inferiorDretaEsperat[i].getX() << ", " <<
			inferiorDretaEsperat[i].getY() << ")" << endl;
		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Punt superior esquerra obtingut: " <<
			"(" << superiorEsquerraObtingut.getX() << ", " <<
			superiorEsquerraObtingut.getY() << ")" << endl;
		cout << "Comment :=>> Punt inferior dreta obtingut: " <<
			"(" << inferiorDretaObtingut.getX() << ", " <<
			inferiorDretaObtingut.getY() << ")" << endl;
		if ((superiorEsquerraEsperat[i].getX() == superiorEsquerraObtingut.getX()) &&
			(superiorEsquerraEsperat[i].getY() == superiorEsquerraObtingut.getY()) &&
			(inferiorDretaEsperat[i].getX() == inferiorDretaObtingut.getX()) &&
			(inferiorDretaEsperat[i].getY() == inferiorDretaObtingut.getY()))
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	if (reduccio > 4.0)
		reduccio = 4.0;
	return reduccio;
}

float testInterseccio()
{
	const int N_PROVES = 4;
	bool interseccioEsperada[N_PROVES] = { true, true, true, false };

	float reduccio = 0.0;
	bool interseccioObtinguda;

	cout << endl << endl;
	cout << "Comment :=>> Iniciant test de la funcio InterseccioPoligons" << endl;
	cout << "Comment :=>> ==============================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		string nomFitxer;
		ifstream fitxerTest;
		Poligon pol1, pol2;

		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Llegint dades del poligon 1...." << endl;
		nomFitxer = "poligon" + to_string(i + 1) + ".txt";
		llegeixDadesPoligon(pol1, nomFitxer);

		cout << "Comment :=>> Llegint dades del poligon 2...." << endl;
		nomFitxer = "poligon" + to_string(((i + 1) % 4) + 1) + ".txt";
		llegeixDadesPoligon(pol2, nomFitxer);

		interseccioObtinguda = interseccioPoligons(pol1, pol2);

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Resultat esperat de la intersecio: ";
		mostraBool(interseccioEsperada[i]); cout << endl;
		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Resultat obtingut de la intersecio: ";
		mostraBool(interseccioObtinguda); cout << endl;
		if (interseccioEsperada[i] == interseccioObtinguda)
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	if (reduccio > 4.0)
		reduccio = 4.0;
	return reduccio;
}


int main()
{
	float grade = 0.0;

	cout << endl << endl;
	cout << "Comment :=>> INICIANT TEST" << endl;
	cout << "Comment :=>> =============" << endl;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl;

	float reduccio = testCalculaPerimetre();
	grade = grade + (3.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	reduccio = testRectangleMinim();
	grade = grade + (3.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	reduccio = testInterseccio();
	grade = grade + (4.0 - reduccio);

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}