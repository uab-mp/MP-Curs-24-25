#include "../source/assignatura.h"
#include "json.hpp"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

using namespace std;

void mostraBool(bool resultat, stringstream& outputParcial)
{
	if (resultat)
		outputParcial << "CERT";
	else
		outputParcial << "FALS";
}


float testAfegeixNota(Assignatura& assignatura, json& output)
{
	float reduccio = 0.0;
	const int N_PROVES = 9;
	string niu[N_PROVES] = { "NIU_1", "NIU_2", "NIU_3", "NIU_5", "NIU_2", "NIU_2", "NIU_2", "NIU_2", "NIU_2" };
	float nota[N_PROVES] = { 5.0, 4.5, 6.5, 7.5, 5, 5.5, 7.0, 8.0, 6.0 };
	bool resultatEsperat[N_PROVES] = { true, true, true, false, true, true, true, true, false };

	stringstream outputParcial;
	string outputFinal = "";
	output =
	{
		{"name", "TEST AFEGEIX NOTA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << "-----------------------------------------------" << endl;
	outputParcial << "Test del metode afegeixNota " << endl;
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	for (int i = 0; i < N_PROVES; i++)
	{
		bool resultat;

		outputParcial << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "-----------------------------------------------" << endl;
		outputParcial << "Niu estudiant: " << niu[i] << endl;
		outputParcial << "Nota introduida: " << nota[i] << endl;
		outputParcial << "----------" << endl;

		resultat = assignatura.afegeixNota(niu[i], nota[i]);
		outputParcial << "Resultat esperat: ";
		mostraBool(resultatEsperat[i], outputParcial);
		outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: ";
		mostraBool(resultat, outputParcial);
		outputParcial << endl;
		outputParcial << "----------" << endl;
		if (resultatEsperat[i] == resultat)
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
	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	return reduccio;
}


float testCalculaNotaMitjana(Assignatura& assignatura, json& output)
{
	float reduccio = 0.0;
	const int N_PROVES = 4;
	string niu[N_PROVES] = { "NIU_1", "NIU_2", "NIU_4", "NIU_5"};
	float mitjanaEsperada[N_PROVES] = { 5.0, 6.0, -1.0, -1.0 };

	stringstream outputParcial;
	string outputFinal = "";
	output =
	{
		{"name", "TEST CALCULA NOTA MITJANA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << "-----------------------------------------------" << endl;
	outputParcial << "Test del metode calculaNotaMitjana " << endl;
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	for (int i = 0; i < N_PROVES; i++)
	{
		float resultat;

		outputParcial << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "-----------------------------------------------" << endl;
		outputParcial << "Niu estudiant: " << niu[i] << endl;
		outputParcial << "----------" << endl;

		resultat = assignatura.calculaNotaMitjana(niu[i]);
		outputParcial << "Resultat esperat: " << mitjanaEsperada[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << resultat << endl;
		outputParcial << "----------" << endl;
		if (fabs(mitjanaEsperada[i] - resultat) < 0.001)
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
	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	return reduccio;
}

float testRecuperaProfessor(Assignatura& assignatura, json& output)
{
	float reduccio = 0.0;
	string nomEsperat = "PROF_1";
	string mailEsperat = "MAIL_1";
	string despatxEsperat = "DESPATX_1";

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST RECUPERA PROFESSOR"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << "-----------------------------------------------" << endl;
	outputParcial << "Test del metode recuperaProfessor " << endl;
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	outputParcial << endl;
	string nom = assignatura.getNomProfessor();
	string mail = assignatura.getMailProfessor();
	string despatx = assignatura.getDespatxProfessor();
	outputParcial << "Nom professor esperat: " << nomEsperat << endl;
	outputParcial << "Mail professor esperat: " << mailEsperat << endl;
	outputParcial << "Despatx professor esperat: " << despatxEsperat << endl;
	outputParcial << "----------" << endl;
	outputParcial << "Nom professor obtingut: " << nom << endl;
	outputParcial << "Mail professor obtingut: " << mail << endl;
	outputParcial << "Despatx professor obtingut: " << despatx << endl;
	outputParcial << "----------" << endl;
	if ((nom == nomEsperat) && (mail == mailEsperat) && (despatx == despatxEsperat))
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

	stringstream outputParcial;
	string outputGeneral;


	cout << "Grade :=>> " << grade << endl;

	outputParcial << "Inicialitzem l'assignatura amb el constructor amb els estudiants seguents...." << endl;
	outputParcial << "NIU_1, NOM_1" << endl;
	outputParcial << "NIU_2, NOM_2" << endl;
	outputParcial << "NIU_3, NOM_3" << endl;
	outputParcial << "-------------------------------------------------" << endl;

	cout << outputParcial.str();
	outputGeneral += outputParcial.str();
	outputParcial.str("");

	const int nEstudiants = 3;
	string estudiants[MAX_ESTUDIANTS][2] =
	{
		{"NOM_1", "NIU_1"},
		{"NOM_2", "NIU_2"},
		{"NOM_3", "NIU_3"}
	};
	Assignatura assignatura("ASSIG_1", "PROF_1", "MAIL_1", "DESPATX_1", nEstudiants, estudiants);

	outputParcial << "Afegim amb el metode afegeixEStudiant l'estudiant NIU_4, NOM_4" << endl;
	outputParcial << "-------------------------------------------------" << endl;

	cout << outputParcial.str();
	outputGeneral += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputGeneral;

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestAfegeixNota;
	float reduccio = testAfegeixNota(assignatura, outputTestAfegeixNota);
	grade = grade + (4 - reduccio);
	if (grade < 0)
		grade = 0.0;
	output["score"] = grade;
	output["tests"].push_back(outputTestAfegeixNota);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestCalculaNotaMitjana;
	reduccio = testCalculaNotaMitjana(assignatura, outputTestCalculaNotaMitjana);
	grade = grade + (4 - reduccio);
	if (grade < 0)
		grade = 0.0;
	output["score"] = grade;
	output["tests"].push_back(outputTestCalculaNotaMitjana);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestRecuperaProfessor;
	reduccio = testRecuperaProfessor(assignatura, outputTestRecuperaProfessor);
	grade = grade + (2 - reduccio);
	if (grade < 0)
		grade = 0.0;
	output["score"] = grade;
	output["tests"].push_back(outputTestRecuperaProfessor);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}
