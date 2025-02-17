#include "../source/paraulogic.h"
#include <string.h>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;


char diccionari[N_PARAULES][MAX_PARAULA];


void mostraBool(bool resultat, stringstream& outputParcial)
{
	if (resultat)
		outputParcial << "VALIDA";
	else
		outputParcial << "NO VALIDA";
}

void mostraTutti(bool resultat, stringstream& outputParcial)
{
	if (resultat)
		outputParcial << "TUTTI";
	else
		outputParcial << "NO TUTTI";
}


bool llegeixDiccionari()
{
	bool correcte = false;
	const string nomFitxerDiccionari = "diccionari_catala.dic";
	ifstream fitxer;
	fitxer.open(nomFitxerDiccionari);
	if (fitxer.is_open())
	{
		correcte = true;
		char paraula[MAX_PARAULA];
		int i = 0;
		fitxer >> paraula;
		while (!fitxer.eof())
		{
			strcpy(diccionari[i], paraula);
			i++;
			fitxer >> paraula;
		}
	}
	return correcte;
}

float testIntrodueixParaula(json& output)
{
	float reduccio = 0.0;
	const int N_PROVES = 9;


	char lletres[N_LLETRES + 1] = {'b', 'a', 'i', 'x', 'd', 'o', 'r', '\0'};
	char paraules[N_PROVES][MAX_PARAULA] =
	{
		"abaixat",
		"dia",
		"baixadora",
		"bo",
		"bar",
		"baix",
		"barri",
		"baixada",
		"abaixador"
	};
	bool resultatEsperat[N_PROVES] = { false, false, false, true, true, true, true, true, true };
	bool tuttiEsperat[N_PROVES] = { false, false, false, false, false, false, false, false, true };
	int puntuacioEsperada[N_PROVES] = { 0, 0, 0, 0, 1, 2, 5, 7, 18 };
	
	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST INTRODUEIX PARAULA"},
        {"visibility", "visible"},
        {"output", ""}
    };
	

	if (!llegeixDiccionari())
	{
		outputParcial << "ERROR. No es pot llegir el fitxer amb el diccionari" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
		reduccio = 10.0;
	}
	else
	{
		for (int i = 0; i < N_PROVES; i++)
		{
			bool resultat, tutti;
			int puntuacio;

			outputParcial << endl;
			outputParcial << "-----------------------------------------------" << endl;
			outputParcial << "TEST " << i + 1 << endl;
			outputParcial << "-----------------------------------------------" << endl;

			outputParcial << "Lletres disponibles: " << lletres << endl;
			outputParcial << "Paraula introduida: " << paraules[i] << endl;
			outputParcial << "----------" << endl;

			resultat = introdueixParaula(paraules[i], lletres, diccionari, tutti, puntuacio);
			outputParcial << "Resultat esperat: ";
			mostraBool(resultatEsperat[i], outputParcial);
			outputParcial << endl;
			outputParcial << "Tutti esperat: ";
			mostraTutti(tuttiEsperat[i], outputParcial);
			outputParcial << endl;
			outputParcial << "Puntuacio esperada: " << puntuacioEsperada[i] << endl;
			outputParcial << "----------" << endl;
			outputParcial << "Resultat obtingut: ";
			mostraBool(resultat, outputParcial);
			outputParcial << endl;
			outputParcial << "Tutti obtingut: ";
			mostraTutti(tutti, outputParcial);
			outputParcial << endl;
			outputParcial << "Puntuacio obtinguda: " << puntuacio << endl;
			outputParcial << "----------" << endl;
			if ((resultatEsperat[i] == resultat) && (tuttiEsperat[i] == tutti) && (puntuacioEsperada[i] == puntuacio))
				outputParcial << "CORRECTE" << endl;
			else
			{
				outputParcial << "ERROR" << endl;
				reduccio += 2;
			}
			outputParcial << "-----------------------------------------------" << endl;
			cout << outputParcial.str();
			outputFinal += outputParcial.str();
			outputParcial.str("");

		}

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
	json output;
	ofstream jsonFile;
	float grade = 0.0;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "hidden";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestIntrodueixParaula;
	float reduccio = testIntrodueixParaula(outputTestIntrodueixParaula);
	grade = grade + (10 - reduccio);
	output["score"] = grade;
	output["tests"].push_back(outputTestIntrodueixParaula);

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

