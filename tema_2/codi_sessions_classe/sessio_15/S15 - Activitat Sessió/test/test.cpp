#include "../source/titulacio.h"
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

int main()
{
	Titulacio titulacio("nom_titulacio", 10);
	string niu, nom;
	Estudiant estudiant;
	float grade;
	bool correcte = true;

	json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
	output["stdout_visibility"] = "visible";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	grade = 0;

	json outputTestAfegeixEstudiant;
	stringstream outputParcial;

	outputTestAfegeixEstudiant =
	{
		{"name", "TEST AFEGEIX ESTUDIANT"},
		{"visibility", "visible"},
		{"output", ""}
	};



	outputParcial << "TEST afegeix estudiant" << endl;
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Afegint estudiant: 'NIU_1', 'NOM_1' " << endl;
	titulacio.afegeixEstudiant("NIU_1", "NOM_1");
	outputParcial << "Afegint estudiant: 'NIU_2', 'NOM_2' " << endl;
	titulacio.afegeixEstudiant("NIU_2", "NOM_2");
	outputParcial << "------" << endl;
	outputParcial << "Comprovant estudiant: 'NIU_1'" << endl;
	bool resposta = titulacio.consultaEstudiant("NIU_1", estudiant);
	outputParcial << "Valor de retorn esperat: "; mostraBool(true, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	outputParcial << "Valor de retorn obtingut: "; mostraBool(resposta, outputParcial); outputParcial << endl;
	if (resposta)
	{
		outputParcial << "Niu de l'estudiant obtingut: " << estudiant.getNiu() << endl;
		outputParcial << "Nom de l'estudiant obtingut: " << estudiant.getNom() << endl;
	}
	outputParcial << "------" << endl;
	if ((resposta == true) && (estudiant.getNiu() == "NIU_1") && (estudiant.getNom() == "NOM_1"))
	{
		grade += 1.5;
		outputParcial << "CORRECTE" << endl;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		correcte = false;
	}
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Comprovant estudiant: 'NIU_2'" << endl;
	resposta = titulacio.consultaEstudiant("NIU_2", estudiant);
	outputParcial << "Valor de retorn esperat: "; mostraBool(true, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	outputParcial << "Valor de retorn obtingut: "; mostraBool(resposta, outputParcial); outputParcial << endl;
	if (resposta)
	{
		outputParcial << "Niu de l'estudiant obtingut: " << estudiant.getNiu() << endl;
		outputParcial << "Nom de l'estudiant obtingut: " << estudiant.getNom() << endl;
	}
	outputParcial << "------" << endl;
	if ((resposta == true) && (estudiant.getNiu() == "NIU_2") && (estudiant.getNom() == "NOM_2"))
	{
		grade += 1.5;
		outputParcial << "CORRECTE" << endl;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		correcte = false;
	}
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Comprovant estudiant: 'NIU_3'" << endl;
	resposta = titulacio.consultaEstudiant("NIU_3", estudiant);
	outputParcial << "Valor de retorn esperat: "; mostraBool(false, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	outputParcial << "Valor de retorn obtingut: "; mostraBool(resposta, outputParcial); outputParcial << endl;
	if (resposta)
	{
		outputParcial << "Niu de l'estudiant obtingut: " << estudiant.getNiu() << endl;
		outputParcial << "Nom de l'estudiant obtingut: " << estudiant.getNom() << endl;
	}
	outputParcial << "------" << endl;
	if (resposta == false)
	{
		grade += 1.0;
		outputParcial << "CORRECTE" << endl;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		correcte = false;
	}
	outputParcial << "------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTestAfegeixEstudiant["output"] = outputParcial.str();
	outputParcial.str("");

	if (correcte)
		outputTestAfegeixEstudiant["status"] = "passed";
	else
		outputTestAfegeixEstudiant["status"] = "failed";
	output["score"] = grade;
	output["tests"].push_back(outputTestAfegeixEstudiant);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	cout << "Grade :=>> " << grade << endl;


	json outputTestAfegeixAssignatura;

	outputTestAfegeixAssignatura =
	{
		{"name", "TEST AFEGEIX ASSIGNATURA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	correcte = true;

	outputParcial << "TEST afegeix assignatura a estudiant" << endl;
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Afegint assignatura: 'metodologia de la programacio'" << endl;
	estudiant.afegeixAssignatura("metodologia de la programacio");
	outputParcial << "Afegint assignatura: 'algebra'" << endl;
	estudiant.afegeixAssignatura("algebra");
	outputParcial << "------" << endl;
	outputParcial << "Nom de les assignatures guardades a l'array d'assignatures de l'estudiant: " << endl;
	string assignatura = estudiant.getAssignatura(0);
	outputParcial << assignatura << endl;
	if (assignatura == "metodologia de la programacio")
		grade = grade + 1.0;
	else
		correcte = false;
	assignatura = estudiant.getAssignatura(1);
	outputParcial << assignatura << endl;
	outputParcial << "------" << endl;
	if (assignatura == "algebra")
		grade = grade + 1.0;
	else
		correcte = false;
	if (correcte)
	{
		outputParcial << "CORRECTE" << endl;
		outputTestAfegeixAssignatura["status"] = "passed";
	}
	else
	{
		outputParcial << "ERROR" << endl;
		outputTestAfegeixAssignatura["status"] = "failed";
	}
	outputParcial << "------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTestAfegeixAssignatura["output"] = outputParcial.str();
	outputParcial.str("");

	output["score"] = grade;
	output["tests"].push_back(outputTestAfegeixAssignatura);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	cout << "Grade :=>> " << grade << endl;

	json outputTestEliminaEstudiant;

	outputTestEliminaEstudiant =
	{
		{"name", "TEST ELIMINA ESTUDIANT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	correcte = true;

	outputParcial << "TEST elimina estudiant" << endl;
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Eliminant estudiant: 'NIU_1' " << endl;
	outputParcial << "Comprovant estudiant: 'NIU_1'" << endl;
	titulacio.eliminaEstudiant("NIU_1");
	resposta = titulacio.consultaEstudiant("NIU_1", estudiant);
	outputParcial << "Valor de retorn esperat: "; mostraBool(false, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	outputParcial << "Valor de retorn obtingut: "; mostraBool(resposta, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	if (resposta == false)
	{
		grade += 1.0;
		outputParcial << "CORRECTE" << endl;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		correcte = false;
	}
	outputParcial << "------------------------------------------" << endl;
	titulacio.eliminaEstudiant("NIU_2");
	outputParcial << "Comprovant estudiant: 'NIU_2'" << endl;
	resposta = titulacio.consultaEstudiant("NIU_2", estudiant);
	outputParcial << "Valor de retorn esperat: "; mostraBool(false, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	outputParcial << "Valor de retorn obtingut: "; mostraBool(resposta, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	if (resposta == false)
	{
		grade += 1.0;
		outputParcial << "CORRECTE" << endl;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		correcte = false;
	}
	outputParcial << "------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTestEliminaEstudiant["output"] = outputParcial.str();
	outputParcial.str("");

	if (correcte)
		outputTestEliminaEstudiant["status"] = "passed";
	else
		outputTestEliminaEstudiant["status"] = "failed";
	output["score"] = grade;
	output["tests"].push_back(outputTestEliminaEstudiant);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	cout << "Grade :=>> " << grade << endl;

	json outputTestOperadorAssignacio;

	outputTestOperadorAssignacio =
	{
		{"name", "TEST OPERADOR ASSIGNACIO"},
		{"visibility", "visible"},
		{"output", ""}
	};

	correcte = true;

	outputParcial << "TEST Operador Assignacio" << endl;
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Creant Estudiant: 'NIU_3', 'NOM_3 " << endl;
	Estudiant* estudiantOriginal = new Estudiant("NIU_3", "NOM_3", 10);
	outputParcial << "Afegint assignatures a l'estudiant: 'ASSIG_1', 'ASSIG_2" << endl;
	estudiantOriginal->afegeixAssignatura("ASSIG_1");
	estudiantOriginal->afegeixAssignatura("ASSIG_2");
	outputParcial << "Duplicant estudiant amb l'operador d'assignacio" << endl;
	Estudiant nouEstudiant;
	nouEstudiant = *estudiantOriginal;
	delete estudiantOriginal;
	outputParcial << "Recuperant dades de l'estudiant duplicat" << endl;
	outputParcial << "Niu de l'estudiant obtingut: " << nouEstudiant.getNiu() << endl;
	outputParcial << "Nom de l'estudiant obtingut: " << nouEstudiant.getNom() << endl;
	if ((nouEstudiant.getNiu() != "NIU_3") || (nouEstudiant.getNom() != "NOM_3"))
		correcte = false;
	outputParcial << "Nom de les assignatures guardades a l'array d'assignatures de l'estudiant: " << endl;
	assignatura = nouEstudiant.getAssignatura(0);
	outputParcial << assignatura << endl;
	if (assignatura != "ASSIG_1")
		correcte = false;
	assignatura = nouEstudiant.getAssignatura(1);
	outputParcial << assignatura << endl;
	outputParcial << "------" << endl;
	if (assignatura != "ASSIG_2")
		correcte = false;
	if (correcte)
	{
		grade += 2.0;
		outputParcial << "CORRECTE" << endl;
		outputTestOperadorAssignacio["status"] = "passed";
	}
	else
	{
		outputParcial << "ERROR" << endl;
		outputTestOperadorAssignacio["status"] = "failed";
	}
		
	outputParcial << "------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTestOperadorAssignacio["output"] = outputParcial.str();
	outputParcial.str("");

	output["score"] = grade;
	output["tests"].push_back(outputTestOperadorAssignacio);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	cout << "Grade :=>> " << grade << endl;


	if (grade == 10.0)
		outputParcial << "Final del test sense errors" << endl;



 	return 0;
}


