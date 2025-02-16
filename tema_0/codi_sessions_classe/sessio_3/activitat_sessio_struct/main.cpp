#include "poligon.h"
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
	fitxerTest >> nVertexs;
	cout << "Comment :=>> N. de vertexs: " << nVertexs << endl;
	cout << "Comment :=>> Coordenades dels vertexs: ";
	fitxerTest >> x >> y;
	while (!fitxerTest.eof())
	{
		cout << "(" << x << ", " << y << ") ";
		fitxerTest >> x >> y;
	}
	cout << endl;
	fitxerTest.close();
	cout << "Comment :=>> -----" << endl;

	fitxerTest.open(nomFitxer);
	streambuf* buffer_cin = cin.rdbuf(fitxerTest.rdbuf());
	llegeixPoligon(pol);
	cin.rdbuf(buffer_cin);
	fitxerTest.close();
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

		perimetreObtingut = calculaPerimetre(pol);

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Perimetre esperat: " << perimetreEsperat[i] << endl;
		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Perimetre obtingut: " << perimetreObtingut << endl;
		if (perimetreEsperat[i] == perimetreObtingut)
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2.0;
		}
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	if (reduccio > 6.0)
		reduccio = 6.0;
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
	cout << "Comment :=>> Iniciant test de la funcio RectangleMinim" << endl;
	cout << "Comment :=>> =========================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		string nomFitxer;
		ifstream fitxerTest;
		Poligon pol;

		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Llegint dades del poligon...." << endl;
		nomFitxer = "poligon" + to_string(i + 1) + ".txt";
		llegeixDadesPoligon(pol, nomFitxer);

		rectangleMinim(pol, superiorEsquerraObtingut, inferiorDretaObtingut);

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Punt superior esquerra esperat: " <<
			"(" << superiorEsquerraEsperat[i].x << ", " <<
			superiorEsquerraEsperat[i].y << ")" << endl;
		cout << "Comment :=>> Punt inferior dreta esperat: " <<
			"(" << inferiorDretaEsperat[i].x << ", " <<
			inferiorDretaEsperat[i].y << ")" << endl;
		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Punt superior esquerra obtingut: " <<
			"(" << superiorEsquerraObtingut.x << ", " <<
			superiorEsquerraObtingut.y << ")" << endl;
		cout << "Comment :=>> Punt inferior dreta obtingut: " <<
			"(" << inferiorDretaObtingut.x << ", " <<
			inferiorDretaObtingut.y << ")" << endl;
		if ((superiorEsquerraEsperat[i].x == superiorEsquerraObtingut.x) &&
			(superiorEsquerraEsperat[i].y == superiorEsquerraObtingut.y) &&
			(inferiorDretaEsperat[i].x == inferiorDretaObtingut.x) &&
			(inferiorDretaEsperat[i].y == inferiorDretaObtingut.y))
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2.0;
		}
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	if (reduccio > 6.0)
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
	grade = grade + (5.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	reduccio = testRectangleMinim();
	grade = grade + (5.0 - reduccio);

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}