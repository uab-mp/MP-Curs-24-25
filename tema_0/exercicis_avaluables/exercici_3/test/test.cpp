#include "../source/assignacio.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;


bool comparaConjunt(string conjunt1[], int nElements1, string conjunt2[], int nElements2)
{
    bool iguals = (nElements1 == nElements2);
    int i = 0;
    while (iguals && (i < nElements1))
    {
        iguals = false;
        int j = 0;
        while (!iguals && (j < nElements2))
        {
            if (conjunt1[i] == conjunt2[j])
                iguals = true;
            else
                j++;
        }
        i++;
    }
    return iguals;
}

float testAssignacio(json& output)
{
    float reduccio = 0.0;
    Assignacio dadesAssignacio;

    stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST ASSIGNACIO"},
        {"visibility", "visible"},
        {"output", ""}
    };

    outputParcial << "Test de la funció d'assignacio" << endl;
	outputParcial << "==============================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

    int nAssignatures = 4;
    string nomAssignatures[MAX_ASSIGNATURES] = {"ASSIG_1", "ASSIG_2", "ASSIG_3", "ASSIG_4"};
    int maxMatriculats[MAX_ASSIGNATURES] = {3, 5, 3, 3};
    inicialitza(dadesAssignacio, nAssignatures, nomAssignatures, maxMatriculats);

    outputParcial << endl;
    outputParcial << "INICIALITZACIO DE LES DADES D'ASSIGNATURES: " << endl;
    outputParcial << "------------------------------------------" << endl;
    for (int i = 0; i < nAssignatures; i++)
    {
        outputParcial << "Nom Assignatura: " << nomAssignatures[i] << endl;
        outputParcial << "Max. matriculats: " << maxMatriculats[i] << endl;
        outputParcial << "--------------------" << endl;
    }
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");

    int nEstudiants = 5;
    string nomEstudiants[MAX_ESTUDIANTS] = {"ESTUDIANT_1", "ESTUDIANT_2", "ESTUDIANT_3", "ESTUDIANT_4", "ESTUDIANT_5"};
    int nCreditsSuperats[MAX_ESTUDIANTS] = {60, 50, 60, 30, 30};
    float notaMitjana[MAX_ESTUDIANTS] = {7.5, 6.5, 8.5, 5.5, 6.5};
    int nAssignaturesAMatricular[MAX_ESTUDIANTS] = {3, 3, 3, 3, 3};
    int nAssignaturesPreferides[MAX_ESTUDIANTS] = {4, 4, 3, 3, 4};

    string assignaturesPreferides[MAX_ESTUDIANTS][MAX_ASSIGNATURES] = 
    {
        {"ASSIG_1", "ASSIG_2", "ASSIG_3", "ASSIG_4"}, 
        {"ASSIG_1", "ASSIG_2", "ASSIG_3", "ASSIG_4"}, 
        {"ASSIG_1", "ASSIG_2", "ASSIG_4"}, 
        {"ASSIG_2", "ASSIG_3", "ASSIG_4"}, 
        {"ASSIG_1", "ASSIG_2", "ASSIG_3", "ASSIG_4"}
    };

    outputParcial << endl;
    outputParcial << "INICIALITZACIO DE LES DADES DELS ESTUDIANTS: " << endl;
    outputParcial << "--------------------------------------------" << endl;
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");
    for (int i = 0; i < nEstudiants; i++)
    {
        afegeixPreferenciesEstudiant(dadesAssignacio, nomEstudiants[i], nCreditsSuperats[i], notaMitjana[i], nAssignaturesAMatricular[i], nAssignaturesPreferides[i], assignaturesPreferides[i]);
        outputParcial << "Nom Estudiant: " << nomEstudiants[i] << endl;
        outputParcial << "N. Credits: " << nCreditsSuperats[i] << ", Nota Mitjana: " << notaMitjana[i] << ", N. Assignatures a matricular: " << nAssignaturesAMatricular[i] << ", N. Assignatures Preferides: " << nAssignaturesPreferides[i] << endl;
        outputParcial << "Assignatures Preferides: ";
        for (int j = 0; j < nAssignaturesPreferides[i]; j++)
            outputParcial << assignaturesPreferides[i][j] << " ";
        outputParcial << endl;
        outputParcial << "--------------------" << endl;
        cout << outputParcial.str();
        outputFinal += outputParcial.str();
        outputParcial.str("");
    }
        
    string assignaturesAssignadesEsperat[MAX_ESTUDIANTS][MAX_ASSIGNATURES] =
    {
        {"ASSIG_1", "ASSIG_2", "ASSIG_3"},
        {"ASSIG_1", "ASSIG_2", "ASSIG_3"},
        {"ASSIG_1", "ASSIG_2", "ASSIG_4"},
        {"ASSIG_2", "ASSIG_4"},
        {"ASSIG_2", "ASSIG_3", "ASSIG_4"}
    };
    int nAssignaturesAssignadesEsperat[MAX_ESTUDIANTS] = {3, 3, 3, 2, 3};
    string estudiantsMatriculatsEsperat[MAX_ASSIGNATURES][MAX_ESTUDIANTS] =
    {
        {"ESTUDIANT_1", "ESTUDIANT_2", "ESTUDIANT_3"},
        {"ESTUDIANT_1", "ESTUDIANT_2", "ESTUDIANT_3", "ESTUDIANT_5", "ESTUDIANT_4"},
        {"ESTUDIANT_1", "ESTUDIANT_2", "ESTUDIANT_5"},
        {"ESTUDIANT_3", "ESTUDIANT_5", "ESTUDIANT_4"}
    };
    int nEstudiantsMatriculatsEsperat[MAX_ASSIGNATURES] = {3, 5, 3, 3, 3};

    fesAssignacio(dadesAssignacio);

    outputParcial << endl;
    outputParcial << "RESULTAT DE L'ASSIGNACIO: " << endl;
    outputParcial << "------------------------" << endl;
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");
    for (int i = 0; i < nEstudiants; i++)
    {
        int nAssignatures;
        string assignaturesAssignades[MAX_ASSIGNATURES];
        assignaturesEstudiant(dadesAssignacio, nomEstudiants[i], nAssignatures, assignaturesAssignades);
        outputParcial << "Estudiant: " << nomEstudiants[i] << endl;
        outputParcial << "Assignatures Esperades: ";
        for (int j = 0; j < nAssignaturesAssignadesEsperat[i]; j++)
            outputParcial << assignaturesAssignadesEsperat[i][j] << " ";
        outputParcial << endl;
        outputParcial << "------" << endl;
        outputParcial << "Assignatures Obtingudes: ";
        for (int j = 0; j < nAssignatures; j++)
            outputParcial << assignaturesAssignades[j] << " ";
        outputParcial << endl;
        outputParcial << "------" << endl;
        bool correcte = comparaConjunt(assignaturesAssignades, nAssignatures, assignaturesAssignadesEsperat[i], nAssignaturesAssignadesEsperat[i]);
        if (correcte)
            outputParcial << "CORRECTE" << endl;
        else
        {
            outputParcial << "ERROR" << endl;
            reduccio += 2.0;            
        }
        outputParcial << "--------------------------" << endl;
        cout << outputParcial.str();
        outputFinal += outputParcial.str();
        outputParcial.str("");
    }

    for (int i = 0; i < nAssignatures; i++)
    {
        int nEstudiants;
        string estudiantsMatriculats[MAX_ESTUDIANTS];
        estudiantsAssignatura(dadesAssignacio, nomAssignatures[i], nEstudiants, estudiantsMatriculats);
        outputParcial << "Assignatura: " << nomAssignatures[i] << endl;
        outputParcial << "Estudiants Esperats: ";
        for (int j = 0; j < nEstudiantsMatriculatsEsperat[i]; j++)
            outputParcial << estudiantsMatriculatsEsperat[i][j] << " ";
        outputParcial << endl;
        outputParcial << "------" << endl;
        outputParcial << "Estudiants Obtinguts: ";
        for (int j = 0; j < nEstudiants; j++)
            outputParcial << estudiantsMatriculats[j] << " ";
        outputParcial << endl;
        outputParcial << "------" << endl;
        bool correcte = comparaConjunt(estudiantsMatriculats, nEstudiants, estudiantsMatriculatsEsperat[i], nEstudiantsMatriculatsEsperat[i]);
        if (correcte)
            outputParcial << "CORRECTE" << endl;
        else
        {
            outputParcial << "ERROR" << endl;
            reduccio += 2.0;            
        }
        outputParcial << "--------------------------" << endl;
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

    json outputTestAssignacio;
	float reduccio = testAssignacio(outputTestAssignacio);
	grade = grade + (10 - reduccio);
    if (grade < 0)
        grade = 0.0;
    cout << endl << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestAssignacio);

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

    if (grade == 10.0)
        cout << "Final del test sense errors" << endl;

    return 0;
}