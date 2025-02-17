#include "..\source\interseccio.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

template<typename T>
void mostraArray(T v[], int longitud, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < longitud - 1; i++)
		outputParcial << v[i] << ", ";
	if (longitud > 0)
		outputParcial << v[longitud - 1];
	outputParcial << "]";
}

bool comparaVector(int v1[], int longitud1, int v2[], int longitud2)
{
	bool iguals = (longitud1 == longitud2);
	int i = 0;
	while ((iguals) && (i < longitud1))
	{
		if (v1[i] != v2[i])
			iguals = false;
		i++;
	}
	return iguals;
}

float testInterseccioOrdenats(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 5;
	const int MAX_ELEMENTS = 10;

	int vector1[N_PROVES][MAX_ELEMENTS] = { { 1, 3, 5, 6, 9 },{ 1, 2, 3, 4, 5 },{ 6, 7, 8, 9 },{ 2, 4, 6, 8 },{1, 3, 5, 7, 9} };
	int vector2[N_PROVES][MAX_ELEMENTS] = { { 2, 4, 6, 7, 8, 13 },{ 3, 4, 5, 6, 7, 8, 9 },{ 3, 5, 6, 7, 8, 9 },{ 2, 4, 6, 8, 10, 12 },{2, 4, 6, 8, 10} };
	int vectorInterseccioEsperat[N_PROVES][MAX_ELEMENTS] = {
		{ 6 },
		{ 3, 4, 5 },
		{ 6, 7, 8, 9 },
		{ 2, 4, 6, 8 },
		{  } };
	int midaVector1[N_PROVES] = { 5, 5, 4, 4, 5 };
	int midaVector2[N_PROVES] = { 6, 7, 6, 6, 5 };
	int midaVectorInterseccioEsperat[N_PROVES] = { 1, 3, 4, 4, 0 };
	int vectorInterseccio[MAX_ELEMENTS];
	int midaVectorInterseccio = 0;


	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST INTERSECCIO VECTORS ORDENATS"},
        {"visibility", "visible"},
        {"output", ""}
    };
	
	outputParcial << endl << endl;
	outputParcial << "Iniciant test Interseccio Vectors Ordenats" << endl;
	outputParcial << "==========================================" << endl;
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Vector1: ";
		mostraArray(vector1[i], midaVector1[i], outputParcial);
		outputParcial << endl;
		outputParcial << "Vector2: ";
		mostraArray(vector2[i], midaVector2[i], outputParcial);
		outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat:";
		mostraArray(vectorInterseccioEsperat[i], midaVectorInterseccioEsperat[i], outputParcial);
		outputParcial << endl;
		interseccioVectorsOrdenats(vector1[i], midaVector1[i], vector2[i], midaVector2[i], vectorInterseccio, midaVectorInterseccio);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut:";
		mostraArray(vectorInterseccio, midaVectorInterseccio, outputParcial);
		outputParcial << endl;
		if (comparaVector(vectorInterseccio, midaVectorInterseccio, vectorInterseccioEsperat[i], midaVectorInterseccioEsperat[i]))
		{
			outputParcial << "CORRECTE" << endl;
		}
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

float testInterseccio(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 5;
	const int MAX_ELEMENTS = 10;

	int vector1[N_PROVES][MAX_ELEMENTS] = { { 1, 6, 5, 3, 9 },{ 5, 2, 1, 4, 3 },{ 6, 7, 8, 9 },{ 2, 4, 6, 8, 10, 12 },{1, 3, 5, 7, 9} };
	int vector2[N_PROVES][MAX_ELEMENTS] = { { 4, 2, 8, 7, 6, 13 },{ 9, 8, 7, 6, 5, 4, 3 },{ 9, 8, 7, 6, 5, 3 },{ 6, 8, 10, 12 },{2, 4, 6, 8, 10} };
	int vector1Esperat[N_PROVES][MAX_ELEMENTS] = {
		{ 6 },
		{ 5, 4, 3 },
		{ 6, 7, 8, 9 },
		{ 6, 8, 10, 12 },
		{  } };
	int midaVector1[N_PROVES] = { 5, 5, 4, 6, 5 };
	int midaVector2[N_PROVES] = { 6, 7, 6, 4, 5 };
	int midaVector1Esperat[N_PROVES] = { 1, 3, 4, 4, 0 };
	
	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST INTERSECCIO VECTORS NO ORDENATS"},
        {"visibility", "visible"},
        {"output", ""}
    };
	outputParcial << endl << endl;
	outputParcial << "Iniciant test Interseccio Vectors No Ordenats" << endl;
	outputParcial << "=============================================" << endl;
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Vector1: ";
		mostraArray(vector1[i], midaVector1[i], outputParcial);
		outputParcial << endl;
		outputParcial << "Vector2: ";
		mostraArray(vector2[i], midaVector2[i], outputParcial);
		outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat:";
		mostraArray(vector1Esperat[i], midaVector1Esperat[i], outputParcial);
		outputParcial << endl;
		interseccioVectors(vector1[i], midaVector1[i], vector2[i], midaVector2[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut:";
		mostraArray(vector1[i], midaVector1[i], outputParcial);
		outputParcial << endl;
		if (comparaVector(vector1[i], midaVector1[i], vector1Esperat[i], midaVector1Esperat[i]))
		{
			outputParcial << "CORRECTE" << endl;
		}
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

	cout << endl << endl;
	cout << "INICIANT TEST" << endl;
	cout << "=============" << endl;
	cout << "" << endl;

	cout << "Grade :=>> " << grade << endl;
	json outputTestInterseccio;
	float reduccio = testInterseccio(outputTestInterseccio);
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade = grade + (5 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestInterseccio);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestInterseccioOrdenats;
	reduccio = testInterseccioOrdenats(outputTestInterseccioOrdenats);
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade = grade + (5 - reduccio);
	output["score"] = grade;
	output["tests"].push_back(outputTestInterseccioOrdenats);
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