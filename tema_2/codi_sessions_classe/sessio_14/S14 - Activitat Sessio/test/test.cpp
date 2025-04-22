#include "../source/seient.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraBool(bool logic, stringstream& outputParcial)
{
	if (logic)
		outputParcial << "TRUE";
	else
		outputParcial << "FALSE";
}

void mostraPassatger(Passatger* p, stringstream& outputParcial)
{
	if (p == nullptr)
		outputParcial << "nullptr";
	else
		if (p->getDni() == "")
			outputParcial << "nullptr";
		else
			outputParcial << p->getDni() << ", " << p->getNom();
}


bool igualsPassatgers(Passatger* pObtingut, Passatger* pEsperat)
{
	bool iguals = false;
	if (pObtingut == nullptr)
	{
		if (pEsperat == nullptr)
			iguals = true;
		else
			if (pEsperat->getDni() == "")
				iguals = true;
	}
	else
		if (pEsperat != nullptr)
			iguals = (pObtingut->getDni() == pEsperat->getDni()) && (pObtingut->getNom() == pEsperat->getNom());
	return iguals;
}

float testSeient(json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	json outputTest;
	stringstream outputParcial;
	ofstream jsonFile;

	outputTest =
	{
		{"name", "TEST INICIALITZACIO CLASSE SEIENT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << " TEST INICIALITZACIO SEIENT" << endl;
	outputParcial << " --------------------------" << endl;
	outputParcial << "" << endl;
	outputParcial << " Inicialitzant un seient amb codi 1A" << endl;
	Seient s("1A");

	outputParcial << " ---" << endl;
	outputParcial << " Valor esperat del passatger despres d'inicialitzar: ";
	mostraPassatger(nullptr, outputParcial);
	outputParcial << endl;
	outputParcial << " ---" << endl;
	outputParcial << " Valor obtingut del passatger despres d'inicialitzar: ";
	Passatger* p = s.getPassatger();
	mostraPassatger(p, outputParcial);
	outputParcial << endl;
	if (!igualsPassatgers(p, nullptr))
	{
		outputTest["status"] = "failed";
		outputParcial << " ERROR" << endl;
		reduccio += 2.5;
	}
	else
	{
		outputTest["status"] = "passed";
		outputParcial << " CORRECTE" << endl;
		grade += 2.0;
	}
	outputParcial << "-----------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();

	const int N_PROVES = 4;
	Passatger valorEsperat[N_PROVES] =
	{
		{ "dni_1", "nom_1" },
		{ "dni_1", "nom_1" },
		{ "", "" },
		{ "", "" }
	};
	bool resultatEsperat[N_PROVES] = { true, false, true, false };

	char operacio[N_PROVES] = { 'A', 'A', 'E', 'E' };
	Passatger dadesPassatger[N_PROVES] =
	{
		{ "dni_1", "nom_1" },
		{ "dni_2", "nom_2" },
		{ "", "" },
		{ "", "" }
	};



	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
		stringstream outputParcial;
		ofstream jsonFile;

		outputTest =
		{
			{"name", "TEST CLASSE SEIENT" + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		bool resultat;
		Passatger* p;
		outputParcial << " TEST " << i + 1 << endl;
		if (operacio[i] == 'A')
		{
			outputParcial << " Afegint passatger al seient..." << endl;
			outputParcial << " Dades del passatger: "; mostraPassatger(&dadesPassatger[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			outputParcial << " Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " Passatger esperat: "; mostraPassatger(&valorEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			resultat = s.assignaPassatger(dadesPassatger[i].getDni(), dadesPassatger[i].getNom());
			p = s.getPassatger();
			outputParcial << " Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
			outputParcial << " Passatger obtingut: "; mostraPassatger(p, outputParcial); outputParcial << endl;
		}
		else
		{
			outputParcial << " Eliminant el passatger del seient..." << endl;
			outputParcial << " ---" << endl;
			outputParcial << " Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " Passatger esperat: "; mostraPassatger(&valorEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			resultat = s.eliminaPassatger();
			p = s.getPassatger();
			outputParcial << " Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
			outputParcial << " Passatger obtingut: "; mostraPassatger(p, outputParcial); outputParcial << endl;
		}

		if ((resultat == resultatEsperat[i]) && igualsPassatgers(p, &valorEsperat[i]))
		{
			outputTest["status"] = "passed";
			outputParcial << " CORRECTE" << endl;
			grade += 2.0;
		}
			
		else
		{
			outputTest["status"] = "failed";
			outputParcial << " ERROR" << endl;
			reduccio += 2.5;
		}
		outputParcial << " ------------------------------------------" << endl;
		
		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		outputGeneral["score"] = grade;
		outputGeneral["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << outputGeneral << endl;
		jsonFile.close();
	}
	if (reduccio > 10.0)
		reduccio = 10.0;
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

	float reduccio = testSeient(output);
	grade = grade + (10 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade == 10.0)
		cout << " Final del test sense errors" << endl;
	return 0;
}