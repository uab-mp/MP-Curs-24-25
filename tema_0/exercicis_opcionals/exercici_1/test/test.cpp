#include "../source/binari.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraBinari(int v[], int longitud, stringstream& outputParcial)
{
	for (int i = 0; i < longitud; i++)
		outputParcial << v[i];
	outputParcial << endl;
}

int testConversio(json& output)
{
	const int N_PROVES = 8;
	const int MAX_BINARI = 16;
	int binari[N_PROVES][MAX_BINARI] =
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 1, 0 },
		{ 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 1, 0, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	int longitud[N_PROVES] = { 4, 4, 8, 8, 8, 8, 16, 16 };
	int resultat[N_PROVES] = { 0, -1, 85, 42, -86, -117, -32513, 255 };

	float reduccio = 0.0;
	int valor;

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST CONVERSIO BINARI A DECIMAL"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de conversio amb signe" << endl;
	outputParcial << "======================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Numero binari a convertir: ";
		mostraBinari(binari[i], longitud[i], outputParcial);
		valor = BinariADecimal(binari[i], longitud[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: " << resultat[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << valor << endl;
		if (valor == resultat[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR " << endl;
			reduccio += 2.0;
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

int main()
{
	json output;
	ofstream jsonFile;
	float grade = 0.0;
	float reduccio;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "hidden";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	cout << endl << endl;
	cout << "INICIANT TEST" << endl;
	cout << "=============" << endl;
	
	json outputTestConversio;
		reduccio = testConversio(outputTestConversio);
	if (reduccio > 10)
		reduccio = 10.0;
	grade = grade + (10 - reduccio);
	output["score"] = grade;
	output["tests"].push_back(outputTestConversio);

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