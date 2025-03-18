#include "../source/tauler.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraTauler(char tauler[N_FILES][N_COLUMNES], stringstream& outputParcial)
{
	for (int i = 0; i < N_FILES; i++)
	{
		outputParcial << "[";
		for (int j = 0; j < (N_COLUMNES - 1); j++)
		{
			outputParcial << tauler[i][j] << ",";
		}
		outputParcial << tauler[i][N_COLUMNES - 1] << "]" << endl;
	}
}

bool igualTauler(char tauler1[N_FILES][N_COLUMNES], char tauler2[N_FILES][N_COLUMNES])
{
	bool iguals = true;
	int i = 0;
	while ((i < N_FILES) && iguals)
	{
		int j = 0;
		while ((j < N_COLUMNES) && iguals)
		{
			if (tauler1[i][j] != tauler2[i][j])
				iguals = false;
			else
				j++;
		}
		i++;
	}
	return iguals;
}

void mostraFitxer(string fitxer[], int nLinies, stringstream& outputParcial)
{
	for (int i = 0; i < nLinies; i++)
	{
		outputParcial << fitxer[i] << endl;
	}
}

void llegeixFitxer(const string& nomFitxer, string fitxer[], int& nLinies)
{
	ifstream fitxerIn(nomFitxer);
	if (fitxerIn.is_open())
	{
		nLinies = 0;
		while (!fitxerIn.eof())
		{
			getline(fitxerIn, fitxer[nLinies]);
			nLinies++;
		}
		fitxerIn.close();
	}
}

bool igualLinia(const string& linia, string fitxer[], int nLinies)
{
	int i = 0;
	bool igual = (linia == "");
	while ((i < nLinies) && !igual)
	{
		if (linia == fitxer[i])
			igual = true;
		else
			i++;
	}
	return igual;
}

bool igualFitxer(string fitxer1[], int nLinies1, string fitxer2[], int nLinies2)
{
	bool iguals = true;
	int i = 0;
	while ((i < nLinies1) && iguals)
	{
		if (!igualLinia(fitxer1[i], fitxer2, nLinies2))
			iguals = false;
		else
			i++;
	}
	i = 0;
	while ((i < nLinies2) && iguals)
	{
		if (!igualLinia(fitxer2[i], fitxer1, nLinies1))
			iguals = false;
		else
			i++;
	}
	return iguals;
}

float testLlegeixTauler(char tauler[N_FILES][N_COLUMNES], json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST LLEGIR TAULER"},
		{"visibility", "visible"},
		{"output", ""}
	};

	char taulerEsperat[N_FILES][N_COLUMNES] =
	{
		{' ', 'X', ' ', 'D', ' ', ' ', ' ', 'X' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ' },
		{ 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', 'O', ' ', ' ', ' ', ' ', ' ', 'X' },
		{ 'O', ' ', 'O', ' ', 'D', ' ', ' ', ' ' }
	};
	outputParcial << endl << endl;
	outputParcial << "Iniciant test de LLEGIR TAULER" << endl;
	outputParcial << "==============================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");


	outputParcial << "Llegint el tauler del fitxer" << endl;	
	const string nomFitxerEntrada = "dames_input.txt";
	llegeixTauler(nomFitxerEntrada, tauler);
	outputParcial << "----------" << endl;
	outputParcial << "Contingut esperat del tauler:" << endl;
	mostraTauler(taulerEsperat, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Contingut obtingut del tauler: " << endl;
	outputParcial << "----------" << endl;
	mostraTauler(tauler, outputParcial);

	if (igualTauler(tauler, taulerEsperat))
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 5.0;
	}
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	return reduccio;
}

float testEscriuTauler(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST ESCRIURE TAULER"},
		{"visibility", "visible"},
		{"output", ""}
	};

	char tauler[N_FILES][N_COLUMNES] =
	{
		{' ', 'X', ' ', 'D', ' ', ' ', ' ', 'X' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ' },
		{ 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O' },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', 'O', ' ', ' ', ' ', ' ', ' ', 'X' },
		{ 'O', ' ', 'O', ' ', 'D', ' ', ' ', ' ' }
	};

	const int MAX_LINIES = 20;
	string fitxerEsperat[MAX_LINIES] = 
	{
		"O a1", 
		"O c1",
		"D e1",
		"O b2",
		"O h4",
		"D d8",
		"X b8",
		"X h8",
		"R a5",
		"X g7",
		"X f6",
		"X h2"
	};
	int nLiniesEsperades = 12;	
	string fitxerObtingut[MAX_LINIES];
	int nLiniesObtingudes = 0;


	outputParcial << endl << endl;
	outputParcial << "Iniciant test de ESCRIURE TAULER" << endl;
	outputParcial << "================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");


	outputParcial << "Contingut del tauler original:" << endl;
	mostraTauler(tauler, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Contingut esperat del fitxer: " << endl;
	mostraFitxer(fitxerEsperat, nLiniesEsperades, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Escrivint el tauler al fitxer" << endl;
	const string nomFitxerSortida = "dames_output.txt";
	escriuTauler(nomFitxerSortida, tauler);
	outputParcial << "----------" << endl;
	llegeixFitxer(nomFitxerSortida, fitxerObtingut, nLiniesObtingudes);
	outputParcial << "Contingut obtingut del fitxer: " << endl;
	mostraFitxer(fitxerObtingut, nLiniesObtingudes, outputParcial);
	outputParcial << "----------" << endl;

	if (igualFitxer(fitxerEsperat, nLiniesEsperades, fitxerObtingut, nLiniesObtingudes))
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 5.0;
	}
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

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
	output["stdout_visibility"] = "visible";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

    char tauler[N_FILES][N_COLUMNES];

	json outputTestLlegeixTauler;
	float reduccio = testLlegeixTauler(tauler, outputTestLlegeixTauler);
	grade = grade + (5 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestLlegeixTauler);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestEscriuTauler;
	reduccio = testEscriuTauler(outputTestEscriuTauler);
	grade = grade + (5 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestEscriuTauler);
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