#include "../source/matriu.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraMatriuEstatica(int matriu[][4], int nFiles, int nColumnes, stringstream& outputParcial)
{
	for (int i = 0; i < nFiles; i++)
	{
		outputParcial << "";
		for (int j = 0; j < nColumnes; j++)
			outputParcial << matriu[i][j] << " ";
		outputParcial << "\n";
	}
}


void mostraMatriuDinamica(int** matriu, int nFiles, int nColumnes, stringstream& outputParcial)
{
	for (int i = 0; i < nFiles; i++)
	{
		outputParcial << "";
		for (int j = 0; j < nColumnes; j++)
			outputParcial << matriu[i][j] << " ";
		outputParcial << "\n";
	}
}

bool igualMatrius(int resultat[][4], int** matriu, int nFiles, int nColumnes)
{
	bool iguals = true;
	int i = 0;
	while (iguals && (i < nFiles))
	{
		int j = 0;
		while (iguals && (j < nColumnes))
		{
			if (resultat[i][j] != matriu[i][j])
				iguals = false;
			else
				j++;
		}
		i++;
	}
	return iguals;
}

int main()
{
	int **m1, **m2, **suma;
	const int nFiles = 5;
	const int nColumnes = 4;

	int matriu1[nFiles][nColumnes] =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16},
		{17, 18, 19, 20}
	};

	int matriu2[nFiles][nColumnes] =
	{
		{1, 1, 1, 1},
		{2, 2, 2, 2},
		{3, 3, 3, 3},
		{4, 4, 4, 4},
		{5, 5, 5, 5}
	};

	int matriuResultat[nFiles][nColumnes] =
	{
		{2, 3, 4, 5},
		{7, 8, 9, 10},
		{12, 13, 14, 15},
		{17, 18, 19, 20},
		{22, 23, 24, 25}
	};

	json output;
	ofstream jsonFile;

	float grade = 0.0;

	output["score"] = grade;
	output["visibility"] = "visible";
	output["stdout_visibility"] = "visible";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	
	cout << "Grade :=>> " << grade << endl;

	json outputTestMatriu;
	stringstream outputParcial;

	outputTestMatriu =
	{
		{"name", "TEST LLEGEIX I SUMA MATRIU DINAMICA"},
		{"visibility", "visible"},
		{"output", ""}
	};


	outputParcial << "Creant les matrius amb 5 files i 4 columnes..." << endl;
	outputParcial << "------------" << endl;

	m1 = creaMatriu(nFiles, nColumnes);
	m2 = creaMatriu(nFiles, nColumnes);
	suma = creaMatriu(nFiles, nColumnes);
	
	outputParcial << "Llegint matriu m1 amb valors..." << endl;
	mostraMatriuEstatica(matriu1, nFiles, nColumnes, outputParcial);
	outputParcial << "------------" << endl;
	llegeixMatriu(m1, nFiles, nColumnes, "matriu1.txt");
	outputParcial << "Valors llegits del fitxer..." << endl;
	mostraMatriuDinamica(m1, nFiles, nColumnes, outputParcial);
	outputParcial << "------------" << endl;
	outputParcial << "Llegint matriu m2 amb valors..." << endl;
	mostraMatriuEstatica(matriu2, nFiles, nColumnes, outputParcial);
	outputParcial << "------------" << endl;
	llegeixMatriu(m2, nFiles, nColumnes, "matriu2.txt");
	outputParcial << "Valors llegits del fitxer..." << endl;
	mostraMatriuDinamica(m2, nFiles, nColumnes, outputParcial);
	outputParcial << "------------" << endl;

	outputParcial << "Calculant la suma de m1 + m2..." << endl;
	sumaMatrius(m1, m2, suma, nFiles, nColumnes);
	outputParcial << "-------------" << endl;
	outputParcial << "Resultat esperat: " << endl;
	mostraMatriuEstatica(matriuResultat, nFiles, nColumnes, outputParcial);
	outputParcial << "------------" << endl;
	outputParcial << "Resultat obtingut: " << endl;
	mostraMatriuDinamica(suma, nFiles, nColumnes, outputParcial);
	outputParcial << "-------------" << endl;

	if (igualMatrius(matriuResultat, suma, nFiles, nColumnes))
	{
		outputParcial << "CORRECTE" << endl;
		outputTestMatriu["status"] = "passed";
		grade += 8;
	}	
	else
	{
		outputParcial << "ERROR" << endl;
		outputTestMatriu["status"] = "failed";
	}
	outputParcial << "-----------------------------------------" << endl;

	cout << outputParcial.str();
	outputTestMatriu["output"] = outputParcial.str();
	outputParcial.str("");

	output["score"] = grade;
	output["tests"].push_back(outputTestMatriu);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	cout << "Grade :=>> " << grade << endl;

	json outputTestAllibera;

	outputTestAllibera =
	{
		{"name", "TEST ALLIBERA MATRIU"},
		{"visibility", "visible"},
		{"output", ""}
	};
	outputParcial << endl;
	outputParcial << "Alliberant totes les matrius..." << endl;

	destrueixMatriu(m1, nFiles);
	destrueixMatriu(m2, nFiles);
	destrueixMatriu(suma, nFiles);

	outputParcial << "-----------------------------------------" << endl;

	grade += 2;

	cout << outputParcial.str();
	outputTestAllibera["output"] = outputParcial.str();
	outputParcial.str("");

	output["score"] = grade;
	output["tests"].push_back(outputTestAllibera);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;

}
