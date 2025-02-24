#include "../source/sudoku.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

using namespace std;

void mostraResultat(bool resultat, stringstream& outputParcial)
{
	if (resultat)
		outputParcial << "VALID";
	else
		outputParcial << "NO VALID";
}

void mostraFinal(bool resultat, stringstream& outputParcial)
{
	if (resultat)
		outputParcial << "PARTIDA FINALITZADA";
	else
		outputParcial << "PARTIDA NO FINALITZADA";
}

void mostraTauler(int tauler[N_FILES][N_COLUMNES], stringstream& outputParcial)
{
	int i, j, k;

	outputParcial << "Valors inicials del sudoku" << endl;
	outputParcial << endl;
	for (i = 0; i < N_FILES; i++)
	{
		if (i % 3 == 0)
		{
			for (k = 0; k < (N_COLUMNES * 2) + 1; k++)
				outputParcial << "=";
			outputParcial << endl;
		}
		for (j = 0; j < N_COLUMNES; j++)
		{
			if (j % 3 == 0)
				outputParcial << "|";
			else
				outputParcial << " ";
			if (tauler[i][j] != 0)
				outputParcial << tauler[i][j];
			else
				outputParcial << " ";
		}
		outputParcial << "|" << endl;
	}
	for (k = 0; k < (N_COLUMNES * 2) + 1; k++)
		outputParcial << "=";
	outputParcial << endl;
	outputParcial << endl;
}



float testSudoku(json& output)
{
	float reduccio = 0.0;
	const int N_PROVES = 2;
	int tauler[N_PROVES][N_FILES][N_COLUMNES] =
	{
		{
			{ 0, 2, 3, 4, 5, 6, 7, 8, 0 },
			{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
			{ 7, 8, 9, 1, 2, 3, 4, 5, 6 },
			{ 2, 3, 4, 5, 6, 7, 8, 9, 1 },
			{ 5, 6, 7, 8, 9, 1, 2, 3, 4 },
			{ 8, 9, 1, 2, 3, 4, 5, 6, 7 },
			{ 3, 4, 5, 6, 7, 8, 9, 1, 2 },
			{ 6, 7, 8, 9, 1, 2, 3, 4, 5 },
			{ 9, 1, 2, 3, 4, 5, 6, 7, 8 },
		},
		{
			{ 0, 0, 3, 4, 5, 6, 7, 8, 0 },
			{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
			{ 7, 8, 0, 1, 2, 3, 0, 5, 6 },
			{ 2, 3, 4, 5, 6, 7, 8, 9, 1 },
			{ 5, 6, 7, 8, 9, 1, 2, 3, 4 },
			{ 8, 0, 1, 2, 3, 4, 5, 6, 7 },
			{ 3, 4, 5, 6, 7, 8, 9, 1, 0 },
			{ 6, 7, 0, 0, 1, 2, 3, 4, 5 },
			{ 9, 1, 2, 3, 4, 5, 6, 7, 8 },
		}
	};
	int nLliures[N_PROVES] = { 2, 9 };
	bool resultatEsperat[N_PROVES][MAX_MOVIMENTS] = 
	{
		{ false, false, true, false},
		{ false, false, false, true, true, false, true, true, true, true, true, true, true}
	};
	bool finalEsperat[N_PROVES] = { false, true };
	int nMovimentsEsperat[N_PROVES] = { 4, 13 };

	ifstream fitxerTest;
	string nomFitxer;
	int nMoviments;
	bool resultat[MAX_MOVIMENTS];

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST SUDOKU"},
        {"visibility", "visible"},
        {"output", ""}
    };

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "" << endl;
		outputParcial << "-----------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "-----------------------------------------------" << endl;

		nomFitxer = "test" + to_string(i+1) + ".txt";
		fitxerTest.open(nomFitxer);
		streambuf* buffer_cin = cin.rdbuf(fitxerTest.rdbuf());

		mostraTauler(tauler[i], outputParcial);

		stringstream outputSudoku;
		streambuf* buffer_cout = cout.rdbuf(outputSudoku.rdbuf());
		bool final = jugaSudoku(tauler[i], nLliures[i], resultat, nMoviments);
		cout.rdbuf(buffer_cout);

		cin.rdbuf(buffer_cin);
		fitxerTest.close();

		outputParcial << "" << endl;
		outputParcial << "N. de moviments esperat: " << nMovimentsEsperat[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "N. de moviments processat: " << nMoviments << endl;
		if (nMovimentsEsperat[i] == nMoviments)
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 2;
		}
		outputParcial << "--------------------" << endl;


		fitxerTest.open(nomFitxer);
		if (fitxerTest.is_open())
		{
			for (int j = 0; j < nMovimentsEsperat[i]; j++)
			{
				int numero, fila, columna;
				fitxerTest >> numero >> fila >> columna;
				outputParcial << "Numero: " << numero << endl;
				outputParcial << "Fila: " << fila << endl;
				outputParcial << "Columna: " << columna << endl;
				outputParcial << "----------" << endl;
				outputParcial << "Resultat esperat: "; mostraResultat(resultatEsperat[i][j], outputParcial); outputParcial << endl;
				outputParcial << "----------" << endl;
				outputParcial << "Resultat obtingut: "; mostraResultat(resultat[j], outputParcial); outputParcial << endl;
				if (resultatEsperat[i][j] == resultat[j])
					outputParcial << "CORRECTE" << endl;
				else
				{
					outputParcial << "ERROR" << endl;
					reduccio += 2;
				}
				outputParcial << "--------------------" << endl;
				cout << outputParcial.str();
				outputFinal += outputParcial.str();
				outputParcial.str("");	
			}
			fitxerTest.close();
		}
		else
			reduccio = 10.0;

	}
	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	return reduccio;
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
	json outputTestSudoku;
	float reduccio = testSudoku(outputTestSudoku);
	grade = grade + (10 - reduccio);
	output["score"] = grade;
	output["tests"].push_back(outputTestSudoku);
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