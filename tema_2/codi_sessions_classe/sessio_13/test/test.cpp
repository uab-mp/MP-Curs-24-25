#include "../source/escola.h"
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


void mostraArrayString(string arrayString[], int nElements, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < (nElements - 1); i++)
		outputParcial << arrayString[i] << ", ";
	if (nElements > 0)
		outputParcial << arrayString[nElements - 1];
	outputParcial << "]" << endl;
}

bool pertanyElement(const string& element, string array[], int nElements)
{
	bool trobat = false;
	int i = 0;
	while ((i < nElements) && !trobat)
	{
		if (element == array[i])
			trobat = true;
		else
			i++;
	}
	return trobat;
}

bool igualArrayString(string array1[], int nElements1, string array2[], int nElements2)
{
	bool iguals = true;
	int i = 0;
	while ((i < nElements1) && iguals)
	{
		if (!pertanyElement(array1[i], array2, nElements2))
			iguals = false;
		else
			i++;
	}
	i = 0;
	while ((i < nElements2) && iguals)
	{
		if (!pertanyElement(array2[i], array1, nElements1))
			iguals = false;
		else
			i++;
	}
	return iguals;
}

void inicialitzaAssignatures(Escola& escola, string& outputFinal)
{
	const int N_ASSIGNATURES = 5;
	string nomsAssignatures[N_ASSIGNATURES] = { "ASSIG_1", "ASSIG_2", "ASSIG_3", "ASSIG_4", "ASSIG_5" };
	stringstream outputParcial;

	outputParcial << "Inicialitzem les assignatures del fitxer assignatures.txt" << endl;
	outputParcial << "---------------------------------------------------------" << endl;
	outputParcial << "Noms de les assignatures: ";
	mostraArrayString(nomsAssignatures, N_ASSIGNATURES, outputParcial);
	escola.inicialitzaAssignatures("assignatures.txt");
	outputParcial << "----------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
}

void inicialitzaProfessors(Escola& escola, string& outputFinal)
{
	const int N_PROFESSORS = 3;
	string nomsProfessors[N_PROFESSORS] = { "PROF_1", "PROF_2", "PROF_3" };
	stringstream outputParcial;
	outputParcial << "Inicialitzem els professors del fitxer professors.txt" << endl;
	outputParcial << "-----------------------------------------------------" << endl;
	outputParcial << "Noms dels professors: ";
	mostraArrayString(nomsProfessors, N_PROFESSORS, outputParcial);
	escola.inicialitzaProfessors("professors.txt");
	outputParcial << "----------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
}

float testAfegeixElimina(Escola& escola, json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	ofstream jsonFile;

	const int N_PROVES = 12;
	char tipusTest[N_PROVES] = { 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'E', 'E', 'E', 'A', 'A' };
	string nomAssignatura[N_PROVES] = { "ASSIG_1", "ASSIG_1", "ASSIG_6","ASSIG_1", "ASSIG_2", "ASSIG_3", 
		"ASSIG_4", "ASSIG_6", "ASSIG_5", "ASSIG_4", "ASSIG_4", "ASSIG_5"};
	string nomProfessor[N_PROVES] = { "PROF_1", "PROF_2", "PROF_1", "PROF_5", "PROF_2", "PROF_1",
		"PROF_3", "", "", "", "PROF_1", "PROF_2" };
	bool resultatEsperat[N_PROVES] = {true, false, false, false, true, true, true, false, false, true, true, true};
	string professorEsperat[N_PROVES] = { "PROF_1", "PROF_1", "", "PROF_1", "PROF_2", "PROF_1",
		"PROF_3", "", "", "", "PROF_1", "PROF_2" };
	string motiuError[N_PROVES] = { "", "Professor no existeix", "Assignatura no existeix", "Assignatura ja te professor",
		"", "", "", "Assignatura no existeix", "Assignatura sense professor", "", "", "" };
	int nTestAfegeix = 0;
	int nTestElimina = 0;

	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
		stringstream outputParcial;
		bool resultat = false;

		if (tipusTest[i] == 'A')
		{
			outputTest =
			{
				{"name", "TEST AFEGEIX PROFESSOR " + to_string(++nTestAfegeix)},
				{"visibility", "visible"},
				{"output", ""}
			};

			outputParcial << "TEST AFEGEIX PROFESSOR " << nTestAfegeix << endl;
			outputParcial << "Nom de l'assignatura: " << nomAssignatura[i] << endl;
			outputParcial << "Nom del professor: " << nomProfessor[i] << endl;
			outputParcial << "----------" << endl;
			outputParcial << "Resultat esperat: ";
			mostraBool(resultatEsperat[i], outputParcial);
			outputParcial << endl;
			if (!resultatEsperat[i])
				outputParcial << "Motiu de l'error: " << motiuError[i] << endl;
			outputParcial << "Professor esperat de l'assignatura: " << professorEsperat[i] << endl;
			outputParcial << "----------" << endl;
			resultat = escola.afegeixProfessorAssignatura(nomAssignatura[i], nomProfessor[i]);
		}
		else
		{
			outputTest =
			{
				{"name", "TEST ELIMINA PROFESSOR " + to_string(++nTestElimina)},
				{"visibility", "visible"},
				{"output", ""}
			};

			outputParcial << "TEST ELIMINA PROFESSOR " << nTestElimina << endl;
			outputParcial << "Nom de l'assignatura: " << nomAssignatura[i] << endl;
			outputParcial << "----------" << endl;
			outputParcial << "Resultat esperat: ";
			mostraBool(resultatEsperat[i], outputParcial);
			outputParcial << endl;
			if (!resultatEsperat[i])
				outputParcial << "Motiu de l'error: " << motiuError[i] << endl;
			outputParcial << "Professor esperat de l'assignatura: " << professorEsperat[i] << endl;
			outputParcial << "----------" << endl;
			resultat = escola.eliminaProfessorAssignatura(nomAssignatura[i]);
		}
		outputParcial << "Resultat obtingut: ";
		mostraBool(resultat, outputParcial);
		outputParcial << endl;
		outputParcial << "Recuperem professor de l'assignatura amb el metode getProfessorAssignatura..." << endl;
		string professor = escola.getProfessorAssignatura(nomAssignatura[i]);
		outputParcial << "Professor obtingut de l'assignatura: " << professor << endl;
		outputParcial << "----------" << endl;
		bool correcte = true;
		if ((resultat == resultatEsperat[i]) && (professor == professorEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			correcte = false;
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "-----------------------------------------------" << endl;

		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		if (correcte)
		{
			outputTest["status"] = "passed";
			grade += 0.5;
		}
		else
			outputTest["status"] = "failed";

		outputGeneral["score"] = grade;
		outputGeneral["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << outputGeneral << endl;
		jsonFile.close();
	}


	if (reduccio > 8.0)
		reduccio = 8.0;

	return reduccio;
}

float testRecuperaAssignaturesProfessor(Escola& escola, json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	ofstream jsonFile;

	const int N_PROVES = 3;
	const int MAX_ASSIGNATURES = 5;
	string nomProfessor[N_PROVES] = { "PROF_1", "PROF_2", "PROF_3" };
	string assignaturesEsperades[N_PROVES][MAX_ASSIGNATURES] =
	{
		{"ASSIG_1", "ASSIG_3", "ASSIG_4"},
		{"ASSIG_2", "ASSIG_5"},
		{""}
	};
	int nAssignaturesEsperades[N_PROVES] = { 3, 2, 0 };

	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
		stringstream outputParcial;
		bool resultat = false;

		outputTest =
		{
			{"name", "TEST RECUPERA ASSIGNATURES PROFESSOR " + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST RECUPERA ASSIGNATURES PROFESSOR " << i + 1 << endl;
		outputParcial << "Nom del professor: " << nomProfessor[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Numero assignatures esperades: " << nAssignaturesEsperades[i] << endl;
		outputParcial << "Assignatures esperades: ";
		mostraArrayString(assignaturesEsperades[i], nAssignaturesEsperades[i], outputParcial);
		outputParcial << "----------" << endl;
		string assignatures[MAX_ASSIGNATURES];
		int nAssignatures = 0;
		escola.getAssignaturesProfessor(nomProfessor[i], assignatures, nAssignatures);
		outputParcial << "Numero assignatures obtingudes: " << nAssignatures << endl;
		outputParcial << "Assignatures obtingures: ";
		mostraArrayString(assignatures, nAssignatures, outputParcial);
		outputParcial << "----------" << endl;
		bool correcte = true;
		if ((nAssignatures == nAssignaturesEsperades[i]) && 
			(igualArrayString(assignaturesEsperades[i], nAssignaturesEsperades[i], assignatures, nAssignatures)))
			outputParcial << "CORRECTE" << endl;
		else
		{
			correcte = false;
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "-----------------------------------------------" << endl;

		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		if (correcte)
		{
			outputTest["status"] = "passed";
			grade += 0.5;
		}
		else
			outputTest["status"] = "failed";

		outputGeneral["score"] = grade;
		outputGeneral["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << outputGeneral << endl;
		jsonFile.close();
	}


	if (reduccio > 2.0)
		reduccio = 2.0;

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

	string outputGeneral;

	Escola escola;
	inicialitzaAssignatures(escola, outputGeneral);
	output["output"] = outputGeneral;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	inicialitzaProfessors(escola, outputGeneral);
	output["output"] = outputGeneral;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	float reduccio = testAfegeixElimina(escola, output);
	grade = grade + (8 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	reduccio = testRecuperaAssignaturesProfessor(escola, output);
	grade = grade + (2 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}
