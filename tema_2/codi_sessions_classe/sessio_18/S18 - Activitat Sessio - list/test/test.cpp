#include "../source/titulacio.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;


float testElimina(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST ELIMINA ESTUDIANTS"},
		{"visibility", "visible"},
		{"output", ""}
	};

	string llistaEsperada =
		"NIU_9, NOM_9, 2017\nNIU_8, NOM_8, 2017\nNIU_7, NOM_7, 2018\nNIU_4, NOM_4, 2018\n";
	Titulacio t;

	outputParcial << "TEST ELIMINA ESTUDIANTS" << endl;
	outputParcial << "-----------------------" << endl;
	outputParcial << "Llegint els estudiants pel fitxer estudiants.txt..." << endl;
	t.llegeixEstudiants("estudiants.txt");
	outputParcial << "Eliminant tots els estudiants anteriors a l'any 2017..." << endl;
	t.eliminaEstudiantsAny(2017);
	outputParcial << "Comprovant el contingut de la llista cridant al metode mostraEstudiants..." << endl;
	stringstream outputLlista;
	streambuf* cout_buf = cout.rdbuf();
	streambuf* string_buf = outputLlista.rdbuf();
	cout.rdbuf(string_buf);
	t.mostraEstudiants();
	cout.flush();
	cout.rdbuf(cout_buf);
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut esperat de la llista: " << endl;
	outputParcial << llistaEsperada << endl;
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut obtingut de la llista: " << endl;
	outputParcial << outputLlista.str() << endl;
	outputParcial << "-----------" << endl;
	if (outputLlista.str() == llistaEsperada)
	{
		outputParcial << "CORRECTE" << endl;
		output["status"] = "passed";
	}
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 5.0;
		output["status"] = "failed";
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	output["output"] = outputFinal;
	return reduccio;
}


float testLlegeix(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST LLEGEIX ESTUDIANTS DEL FITXER"},
		{"visibility", "visible"},
		{"output", ""}
	};

	string llistaEsperada =
		"NIU_9, NOM_9, 2017\nNIU_8, NOM_8, 2017\nNIU_7, NOM_7, 2018\nNIU_6, NOM_6, 2013\nNIU_5, NOM_5, 2014\nNIU_4, NOM_4, 2018\nNIU_3, NOM_3, 2016\nNIU_2, NOM_2, 2015\nNIU_1, NOM_1, 2016\n";
	Titulacio t;

	outputParcial << "TEST LLEGEIX ESTUDIANTS DEL FITXER" << endl;
	outputParcial << "----------------------------------" << endl;
	outputParcial << "Llegint els estudiants pel fitxer estudiants.txt..." << endl;
	t.llegeixEstudiants("estudiants.txt");
	outputParcial << "Comprovant el contingut de la llista cridant al metode mostraEstudiants..." << endl;
	stringstream outputLlista;
	streambuf* cout_buf = cout.rdbuf();
	streambuf* string_buf = outputLlista.rdbuf();
	cout.rdbuf(string_buf);
	t.mostraEstudiants();
	cout.flush();
	cout.rdbuf(cout_buf);
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut esperat de la llista: " << endl;
	outputParcial << llistaEsperada << endl;
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut obtingut de la llista: " << endl;
	outputParcial << outputLlista.str() << endl;
	outputParcial << "-----------" << endl;
	if (outputLlista.str() == llistaEsperada)
	{
		outputParcial << "CORRECTE" << endl;
		output["status"] = "passed";
	}
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 5.0;
		output["status"] = "failed";
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	output["output"] = outputFinal;
	return reduccio;
}


int main()
{
	Titulacio titulacio;
	

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

	cout << "Grade :=>> " << grade << endl;

	json outputTestLlegeix;
	grade += (5 - testLlegeix(outputTestLlegeix));
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestLlegeix);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestElimina;
	grade += (5 - testElimina(outputTestElimina));
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestElimina);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade < 0)
		grade = 0.0;
	if (grade >= 10.0)
	{
		grade = 10;
		cout << "Final del test sense errors" << endl;
	}

 	return 0;
}