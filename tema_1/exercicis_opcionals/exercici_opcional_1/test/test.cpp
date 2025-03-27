
#include "../source/llibre.h"
#include "../source/biblioteca.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "TRUE ";
	else
		outputParcial << "FALSE ";
}


float  testFuncionsLlibre()
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
	stringstream outputParcial;


	float reduccio = 0.0;
	const int MAX_LLIBRES = 4;
	string titol[MAX_LLIBRES] = {
		"Data Structures and Data Analysis in C++",
		"Thinking in C++",
		"Programacion en C++ para ingenieros",
		"The C++ Programming Language"
	};
	string autor[MAX_LLIBRES] = { "Weiss", "Eckel", "Xhafa", "Stroustrup" };
	int nExemplars[MAX_LLIBRES] = { 3, 4, 2, 1 };

	Biblioteca biblio;

	outputParcial <<  endl;
	outputParcial <<  endl;
	outputParcial << "Iniciant test de la classe Biblioteca" << endl;
	outputParcial << "=====================================" << endl;
	outputParcial <<  endl;
	outputParcial << "Afegint llibres amb el metode afegeixLlibre..." << endl;
	cout << outputParcial.str();
	outputGeneral += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < MAX_LLIBRES; i++)
	{
		outputParcial << "llibre " << i+1 << ": " << titol[i] << ", " << autor[i] << ", " << nExemplars[i] << endl;
		Llibre l(titol[i], autor[i], nExemplars[i]);
		biblio.afegeixLlibre(l);
	}
	cout << outputParcial.str();
	outputGeneral += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputGeneral;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();


	const int N_PROVES_PRESTAR = 5;
	int resultatPrestar[N_PROVES_PRESTAR] = { -2, 0, -1, 0, 0};
	string titolPrestar[N_PROVES_PRESTAR] = {
		"Introduction to Databases",
		"The C++ Programming Language",
		"The C++ Programming Language",
		"Thinking in C++",
		"Thinking in C++"
	};
	for (int i = 0; i < N_PROVES_PRESTAR; i++)
	{
		json outputTest;

        outputTest =
        {
            {"name", "TEST PRESTEC LLIBRE " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

		outputParcial << "TEST PRESTEC LLIBRE " << i + 1 << endl;
		outputParcial << "Realitzant prestec de llibre : " << titolPrestar[i] << endl;
		int codiExemplar;
		int resultat = biblio.prestaLlibre(titolPrestar[i], codiExemplar);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: " << resultatPrestar[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << resultat << endl;
		bool correcte = (resultat == resultatPrestar[i]);
		if (correcte)
		
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR";
			reduccio += 1;
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

		if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 1;
        }		    
	    else
		    outputTest["status"] = "failed";

        output["score"] = grade;
        output["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << output << endl;
        jsonFile.close();

	}



	const int N_PROVES_RETORNAR = 5;
	int resultatRetornar[N_PROVES_RETORNAR] = { -2, 0, -1, -1, 0 };
	int codiExemplarRetornar[N_PROVES_RETORNAR] = { 0, 0, 0, 3, 1 };
	string titolRetornar[N_PROVES_RETORNAR] = {
		"Introduction to Databases",
		"The C++ Programming Language",
		"Data Structures and Data Analysis in C++",
		"Thinking in C++",
		"Thinking in C++"
	};
	for (int i = 0; i < N_PROVES_RETORNAR; i++)
	{
		json outputTest;

        outputTest =
        {
            {"name", "TEST RETORNA LLIBRE " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

		outputParcial << "TEST RETORNA LLIBRE " << i + 1 << endl;
		outputParcial << "Realitzant retorn de llibre : " << titolRetornar[i] << ", exemplar: " << codiExemplarRetornar[i] <<  endl;
		int resultat = biblio.retornaLlibre(titolRetornar[i], codiExemplarRetornar[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: " << resultatRetornar[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << resultat << endl;
		bool correcte = (resultat == resultatRetornar[i]);
		if (correcte)
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1;
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

		if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 1;
        }		    
	    else
		    outputTest["status"] = "failed";

        output["score"] = grade;
        output["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << output << endl;
        jsonFile.close();	
	}
	if (reduccio > 10)
		reduccio = 10.0;
	return reduccio;
}

int main()
{
	float grade = 0.0;


	cout << "Grade :=>> " << grade << endl;

	float reduccio = testFuncionsLlibre();
	grade = grade + (10 - reduccio);
	cout << "Grade :=>> " << grade << endl;

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}