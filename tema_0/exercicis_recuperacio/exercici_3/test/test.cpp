#include "../source/domino.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraFitxa(Fitxa& fitxa, stringstream& outputParcial)
{
	int valor1, valor2;
		outputParcial << "(" << fitxa.valor1 << "," << fitxa.valor2 << ") ";
}


void mostraFitxes(Fitxa fitxes[], int nFitxes, stringstream& outputParcial)
{
	for (int i = 0; i < nFitxes; i++)
		mostraFitxa(fitxes[i], outputParcial);
}

bool igualFitxa(Fitxa& fitxa1, Fitxa& fitxa2)
{
	int valorEsq1, valorDreta1, valorEsq2, valorDreta2;
	valorEsq1 = fitxa1.valor1;
	valorDreta1 = fitxa1.valor2;
	valorEsq2 = fitxa2.valor1;
	valorDreta2 = fitxa2.valor2;
	return (((valorEsq1 == valorEsq2) && (valorDreta1 == valorDreta2)) ||
		((valorEsq1 == valorDreta2) && (valorDreta1 == valorEsq2)));
}

bool igualsArray(Fitxa resultatEsperat[], int nFitxesResultatEsperat, Fitxa fitxesJugades[], int nFitxesJugades)
{
	bool iguals = (nFitxesResultatEsperat == nFitxesJugades);
	int i = 0;
	while (iguals && (i < nFitxesResultatEsperat))
	{
		if (!igualFitxa(resultatEsperat[i],  fitxesJugades[i]))
			iguals = false;
		else
			i++;
	}
	return iguals;
}

float testDomino(json& output)
{
	float grade = 0.0;
	const int N_PROVES = 2;
	Fitxa resultatEsperat[N_PROVES][MAX_FITXES*MAX_JUGADORS*2] = 
	{
		{{0, 0}, {-1, -1}, {-1, -1}, {-1, -1}, {0, 1}, {1, 1}, {-1, -1}, {-1, -1}, {0, 2}, {1, 2}, {2, 3}, {3, 6}, {0, 6}, {2, 2}, {2, 4}, {4, 4}, {0, 3}, {1, 3}, {3, 4}, {-1, -1}, {-1, -1}, {1, 4}, {3, 3}, {4, 5}, {0, 5}, {-1, -1}, {3, 5}, {5, 5}, {0, 4} },
		{{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {2, 2}, {2, 3}, {0, 3}, {0, 4}, {2, 6}, {0, 6}, {2, 4}, {2, 5}, {0, 5}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}}
	};
	int nFitxesResultatEsperat[N_PROVES] = { 29, 18 };
	int valorsPartidaEsperat[N_PROVES] = { 1, -1 };

	Fitxa fitxesInicials[N_PROVES][MAX_JUGADORS * MAX_FITXES];
	int nFitxa = 0;
	for (int i = 0; i < 7; i++)
		for (int j = i; j < 7; j++)
		{
			fitxesInicials[0][nFitxa].valor1 = i;
			fitxesInicials[0][nFitxa].valor2 = j;
			nFitxa++;
		}
	nFitxa = 0;
	for (int jugador = 0; jugador < 4; jugador++)
		for (int j = 0; j < 7; j++)
			fitxesInicials[1][nFitxa++] = fitxesInicials[0][(j * 4) + jugador];
	
	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST JUGA PARTIDA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << endl;
		outputParcial << "-----------------------------------------------" << endl;
		outputParcial << "Iniciant test PARTIDA " << i + 1 << endl;
		outputParcial <<  endl;
		outputParcial << "Fitxes inicials per la partida... " << endl;
		mostraFitxes(fitxesInicials[i], MAX_FITXES * MAX_JUGADORS, outputParcial);
		outputParcial << endl;

		outputParcial << "------------------------------" << endl;
		outputParcial << "Jugant la partida cridant a la funcio jugaDomino ..." << endl;
		outputParcial << endl;

		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");

		Fitxa fitxesJugades[MAX_FITXES * MAX_JUGADORS * 2];
		int nFitxesJugades;
		int resultat = jugaDomino(fitxesInicials[i], fitxesJugades, nFitxesJugades);

		outputParcial << "------------------------------" << endl;
		outputParcial << "Jugador guanyador esperat: " << valorsPartidaEsperat[i] << endl;
		outputParcial << "-------" << endl;
		outputParcial << "Jugador guanyador obtingut: " << resultat << endl;
		if (valorsPartidaEsperat[i] == resultat)
		{
			outputParcial << "CORRECTE" << endl;
			grade += 2.5;
		}
		else
			outputParcial << "ERROR" << endl;
		outputParcial << "------------------------------" << endl;

		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");

		cout << "Grade :=>> " << grade << endl;

		outputParcial << "Fitxes jugades esperades: " << endl;
				mostraFitxes(resultatEsperat[i], nFitxesResultatEsperat[i], outputParcial);
		outputParcial << endl;
		outputParcial << "-------" << endl;
		outputParcial << "Fitxes jugades obtingudes: " << endl;
		mostraFitxes(fitxesJugades, nFitxesJugades, outputParcial);
		outputParcial << endl;

		if (igualsArray(resultatEsperat[i], nFitxesResultatEsperat[i], fitxesJugades, nFitxesJugades))
		{
			outputParcial << "CORRECTE" << endl;
			grade += 2.5;
		}
		else
			outputParcial << "ERROR" << endl;
		outputParcial << "------------------------------" << endl;

		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");

		cout << "Grade :=>> " << grade << endl;
	}

	output["output"] = outputFinal;

	if (grade == 10)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	return grade;
}



int main()
{
	float grade = 0.0;
	json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "hidden";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	cout << "Grade :=>> " << grade << endl;
	json outputTestDomino;
	grade = testDomino(outputTestDomino);
	output["score"] = grade;
	output["tests"].push_back(outputTestDomino);

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}