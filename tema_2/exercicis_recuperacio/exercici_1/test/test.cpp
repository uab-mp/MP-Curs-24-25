
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


void testConstructorCopiaLlibre(json& output)
{
	float grade = output["score"];
	ofstream jsonFile;
	string outputGeneral;
	stringstream outputParcial;

	json outputTest;

    outputTest =
    {
		{"name", "TEST CONSTRUCTOR COPIA LLIBRE"},
		{"visibility", "visible"},
		{"output", ""}
    };

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test del constructor de copia de la classe Llibre" << endl;
	outputParcial << "==========================================================" << endl;
	outputParcial << endl;

	outputParcial << "Inicialitzant llibre original: " << endl;
	outputParcial << "-----" << endl;
	outputParcial << "Titol: LLIBRE_1" << endl;	
	outputParcial << "Autor: AUTOR_1" << endl;
	outputParcial << "N.Exemplars: 3" << endl;
	Llibre l1("LLIBRE_1", "AUTOR_1", 3);
	int codiExemplar; 
	l1.presta("NOM_1", "01/01/2025", codiExemplar);
	outputParcial << "-----" << endl;
	outputParcial << "Fent prestec de l'exemplar " << codiExemplar << " amb nom NOM_1 i data 01/01/2025" << endl;
	outputParcial << "--------------------------------------------------------------" << endl;

	bool correcte = true;
	outputParcial << "Inicialitzant copia de llibre amb el constructor de copia: " << endl;
	Llibre l2(l1); 

	outputParcial << "Dades del llibre copiat: " << endl;
	outputParcial << "-----" << endl;
	outputParcial << "Titol: " << l2.getTitol() << endl;
	if (l2.getTitol() != "LLIBRE_1")
		correcte = false;
	outputParcial << "Autor: " << l2.getAutor() << endl;
	if (l2.getAutor() != "AUTOR_1")
		correcte = false;
	outputParcial << "N.Exemplars: " << l2.getNExemplars() << endl;
	if (l2.getNExemplars() != 3)
		correcte = false;
	outputParcial << "-----" << endl;
	outputParcial << "Dades dels exemplars del llibre copiat: " << endl;;
	outputParcial << "-----" << endl;

	const int N_EXEMPLARS = 3;
	bool prestat[N_EXEMPLARS] = {false, false, false};
	prestat[codiExemplar] = true;
	for (int i = 0; i < l2.getNExemplars(); i++)
	{
		Prestec* p = l2.getPrestecExemplar(i);
		if (p != nullptr)
		{
			outputParcial << "Exemplar: " << i << ", Nom Prestec: " << p->getNom() << ", Data Prestec: " << p->getDataPrestec() << endl;
			if (!prestat[i])
				correcte = false;
			else
			{
				if (p->getNom() != "NOM_1" || p->getDataPrestec() != "01/01/2025")
					correcte = false;	
			}
		}
		else
		{
			outputParcial << "Exemplar: " << i << ", No prestat" << endl;
			if (prestat[i])
				correcte = false;	
		}
	}	
	outputParcial << "-----" << endl;

	if (correcte)
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 2.0;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		outputTest["status"] = "failed";
	}

	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
    outputTest["output"] = outputParcial.str();
    outputParcial.str("");

	output["score"] = grade;
    output["tests"].push_back(outputTest);
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();
	cout << "Grade :=>> " << grade << endl;
}


void testOperadorAssignacioLlibre(json& output)
{
	float grade = output["score"];
	ofstream jsonFile;
	string outputGeneral;
	stringstream outputParcial;

	json outputTest;

    outputTest =
    {
		{"name", "TEST OPERADOR ASSIGNACIO LLIBRE"},
		{"visibility", "visible"},
		{"output", ""}
    };

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test de l'operador d'assignacio de la classe Llibre" << endl;
	outputParcial << "============================================================" << endl;
	outputParcial << endl;

	outputParcial << "Inicialitzant llibre original: " << endl;
	outputParcial << "-----" << endl;
	outputParcial << "Titol: LLIBRE_1" << endl;	
	outputParcial << "Autor: AUTOR_1" << endl;
	outputParcial << "N.Exemplars: 3" << endl;
	Llibre l1("LLIBRE_1", "AUTOR_1", 3);
	int codiExemplar; 
	l1.presta("NOM_1", "01/01/2025", codiExemplar);
	outputParcial << "-----" << endl;
	outputParcial << "Fent prestec de l'exemplar " << codiExemplar << " amb nom NOM_1 i data 01/01/2025" << endl;
	outputParcial << "--------------------------------------------------------------" << endl;

	bool correcte = true;
	outputParcial << "Inicialitzant copia de llibre amb l'operador d'assignacio: " << endl;
	Llibre l2;
	l2 = l1; 

	outputParcial << "Dades del llibre copiat: " << endl;;
	outputParcial << "-----" << endl;
	outputParcial << "Titol: " << l2.getTitol() << endl;
	if (l2.getTitol() != "LLIBRE_1")
		correcte = false;
	outputParcial << "Autor: " << l2.getAutor() << endl;
	if (l2.getAutor() != "AUTOR_1")
		correcte = false;
	outputParcial << "N.Exemplars: " << l2.getNExemplars() << endl;
	if (l2.getNExemplars() != 3)
		correcte = false;
	outputParcial << "-----" << endl;
	outputParcial << "Dades dels exemplars del llibre copiat: " << endl;
	outputParcial << "-----" << endl;

	const int N_EXEMPLARS = 3;
	bool prestat[N_EXEMPLARS] = {false, false, false};
	prestat[codiExemplar] = true;
	for (int i = 0; i < l2.getNExemplars(); i++)
	{
		Prestec* p = l2.getPrestecExemplar(i);
		if (p != nullptr)
		{
			outputParcial << "Exemplar: " << i << ", Nom Prestec: " << p->getNom() << ", Data Prestec: " << p->getDataPrestec() << endl;
			if (!prestat[i])
				correcte = false;
			else
			{
				if (p->getNom() != "NOM_1" || p->getDataPrestec() != "01/01/2025")
					correcte = false;	
			}
		}
		else
		{
			outputParcial << "Exemplar: " << i << ", No prestat" << endl;
			if (prestat[i])
				correcte = false;	
		}
	}	
	outputParcial << "-----" << endl;

	if (correcte)
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 2.0;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		outputTest["status"] = "failed";
	}

	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
    outputTest["output"] = outputParcial.str();
    outputParcial.str("");

	output["score"] = grade;
    output["tests"].push_back(outputTest);
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();
	cout << "Grade :=>> " << grade << endl;	
}


void  testFuncionsLlibre(json& output)
{
	float grade = 0.0;
	ofstream jsonFile;
	string outputGeneral;
	stringstream outputParcial;


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

	string nomPrestec[N_PROVES_PRESTAR] = 
	{
		"NOM_1",
		"NOM_2",
		"NOM_3",
		"NOM_4",
		"NOM_5"
	};

	string dataPrestec[N_PROVES_PRESTAR] = 
	{
		"01/01/2025",
		"02/01/2025",
		"03/01/2025",
		"04/01/2025",
		"05/01/2025"
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
		outputParcial << "----------------------" << endl;
		outputParcial << "Realitzant prestec de llibre : " << titolPrestar[i] << " amb nom " << nomPrestec[i] << " i data " << dataPrestec[i] << endl;
		int codiExemplar;
		int resultat = biblio.prestaLlibre(titolPrestar[i], nomPrestec[i], dataPrestec[i], codiExemplar);
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
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

		if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 0.6;
        }		    
	    else
		    outputTest["status"] = "failed";

        output["score"] = grade;
        output["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << output << endl;
        jsonFile.close();
		cout << "Grade :=>> " << grade << endl;
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
		outputParcial << "----------------------" << endl;
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
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

		if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 0.6;
        }		    
	    else
		    outputTest["status"] = "failed";

        output["score"] = grade;
        output["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << output << endl;
        jsonFile.close();	
		cout << "Grade :=>> " << grade << endl;
	}
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


	testFuncionsLlibre(output);

	testConstructorCopiaLlibre(output);

	testOperadorAssignacioLlibre(output);

	grade = output["score"];

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}