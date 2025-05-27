#include "../source/vector.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using json = nlohmann::json;

ostream& operator<<(ostream& out, const Punt& pt)
{
	out << "(" << pt.getX() << "," << pt.getY() << ")";
	return out;
}

void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "TRUE ";
	else
		outputParcial << "FALSE ";
}


bool comparaVector(Vector& v, Punt* resultat, int longitud)
{
	bool iguals = (longitud == v.getNElements());
	if (iguals)
	{
		int i = 0;
		while ((i < longitud) && iguals)
		{
			if (!(resultat[i] == v[i]))
				iguals = false;
			else
				i++;
		}
	}
	return iguals;
}

void mostraVector(Vector &v, int nValors, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < nValors - 1; i++)
	{
		outputParcial << v[i] << ",";
	}
	if (nValors > 0)
		outputParcial << v[nValors - 1];
	outputParcial << "]" << endl;
}

void mostraArray(Punt* v, int nValors, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < nValors - 1; i++)
	{
		outputParcial << v[i] << ",";
	}
	if (nValors > 0)
		outputParcial << v[nValors - 1];
	outputParcial << "]" << endl;
}

void testInsereix(Vector& v, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int MAX_PROVES = 15;

	Punt valors[MAX_PROVES] = { {0, 0},  {9,9}, {8,8}, {7,7}, {6,6},{ 1,1 },{ 2,2 },{3,3},{ 4,4 },{5,5}, {12,12}, {11,11}, {10,10}, {0, 0}, {0, 0} };
	int posicio[MAX_PROVES] = { 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 9, 9, 9, 13, -1 };
	bool resultatEsperat[MAX_PROVES] = { false, true, true, true, true, true, true, true, true, true, true, true, true, false, false };
	int nElementsEsperat[MAX_PROVES] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 12, 12 };
	int maxElementsEsperat[MAX_PROVES] = { 0, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 20, 20, 20, 20 };



	for (int i = 0; i < MAX_PROVES; i++)
	{
		json outputTest =
		{
			{"name", "TEST INSEREIX " + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};
		outputParcial << "TEST INSEREIX " << i + 1 << endl;
		outputParcial << "----------------" << endl;
		outputParcial << "Afegint punt " << valors[i] << " a la posicio " << posicio[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; mostraBool(resultatEsperat[i], outputParcial);
		outputParcial << ", N. elements: " << nElementsEsperat[i] << ", Max elements: " << maxElementsEsperat[i] << endl;
		bool resultat = v.insereix(valors[i], posicio[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultat, outputParcial);
		outputParcial << ", N. elements: " << v.getNElements() << ", Max elements: " << v.getMaxElements() << endl;
		outputParcial << "-----------" << endl;
		if ((resultat == resultatEsperat[i]) && (v.getNElements() == nElementsEsperat[i]) && (v.getMaxElements() == maxElementsEsperat[i]))
		{
			outputParcial << "CORRECTE" << endl;
			outputTest["status"] = "passed";
			grade += 0.2;
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
		cout << endl << "Grade :=>> " << grade << endl << endl;
	}

	json outputTest =
	{
		{"name", "TEST INSEREIX - CONSULTA CONTINGUT FINAL VECTOR"},
		{"visibility", "visible"},
		{"output", ""}
	};
	outputParcial << "TEST INSEREIX - CONSULTA CONTINGUT FINAL VECTOR" << endl;
	outputParcial << "-----------------------------------------------" << endl;
	const int N_ELEMENTS_FINAL = 12;
	Punt contingutEsperat[N_ELEMENTS_FINAL] = {{ 1,1 }, { 2,2 }, { 3,3 }, { 4,4 }, { 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 }, { 11,11 },{ 12,12 }};
	outputParcial << "Contingut final del vector esperat: " << endl; 
	mostraArray(contingutEsperat,	N_ELEMENTS_FINAL, outputParcial);
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut final del vector obtingut: " << endl;
	mostraVector(v, N_ELEMENTS_FINAL, outputParcial);
	outputParcial << "-----------" << endl;
	if (comparaVector(v, contingutEsperat, N_ELEMENTS_FINAL))
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 1.0;
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
	cout << endl << "Grade :=>> " << grade << endl << endl;
}

void testElimina(Vector& v, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int MAX_PROVES = 14;
	const int TEST_CONTINGUT = 11;


	int posicio[MAX_PROVES] = { -1, 12, 0, 10, 1, 7, 2, 6, 3, 2, 0, 0, 0, 0 };
	bool resultatEsperat[MAX_PROVES] = { false, false, true, true, true, true, true, true, true, true, true, true, true, true };
	int nElementsEsperat[MAX_PROVES] = { 12, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	int maxElementsEsperat[MAX_PROVES] = { 20, 20, 20, 20, 20, 20, 20, 20, 20, 10, 10, 10, 5, 5};


	for (int i = 0; i < TEST_CONTINGUT; i++)
	{
		json outputTest =
		{
			{"name", "TEST ELIMINA " + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};		
		outputParcial << "TEST ELIMINA " << i + 1 << endl;
		outputParcial << "--------------" << endl;
		outputParcial << "Eliminant punt de la posicio " << posicio[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; mostraBool(resultatEsperat[i], outputParcial);
		outputParcial << ", N. elements: " << nElementsEsperat[i] << ", Max elements: " << maxElementsEsperat[i] << endl;
		bool resultat = v.elimina(posicio[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultat, outputParcial);
		outputParcial << ", N. elements: " << v.getNElements() << ", Max elements: " << v.getMaxElements() << endl;
		outputParcial << "-----------" << endl;
		if ((resultat == resultatEsperat[i]) && (v.getNElements() == nElementsEsperat[i]) && (v.getMaxElements() == maxElementsEsperat[i]))
		{
			outputParcial << "CORRECTE" << endl;
			outputTest["status"] = "passed";
			grade += 0.2;
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
		cout << endl << "Grade :=>> " << grade << endl << endl;
	}

	json outputTest =
	{
		{"name", "TEST ELIMINA - CONSULTA CONTINGUT VECTOR"},
		{"visibility", "visible"},
		{"output", ""}
	};
	outputParcial << "TEST ELIMINA - CONSULTA CONTINGUT VECTOR" << endl;
	outputParcial << "----------------------------------------" << endl;

	const int N_ELEMENTS_FINAL = 3;
	Punt contingutEsperat[N_ELEMENTS_FINAL] = { { 4,4 },{ 8,8 },{ 9,9 } };
	outputParcial << "Contingut del vector esperat despres de les eliminacions anteriors: " << endl;
	mostraArray(contingutEsperat, N_ELEMENTS_FINAL, outputParcial);
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut del vector obtingut: " << endl;
	mostraVector(v, N_ELEMENTS_FINAL, outputParcial);
	outputParcial << "-----------" << endl;
	if (comparaVector(v, contingutEsperat, N_ELEMENTS_FINAL))
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 1.2;
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
	cout << endl << "Grade :=>> " << grade << endl << endl;

	for (int i = TEST_CONTINGUT; i < MAX_PROVES; i++)
	{
		json outputTest =
		{
			{"name", "TEST ELIMINA " + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};
		outputParcial << "TEST ELIMINA " << i + 1 << endl;
		outputParcial << "--------------" << endl;
		outputParcial << "Eliminant punt de la posicio " << posicio[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; mostraBool(resultatEsperat[i], outputParcial);
		outputParcial << ", N. elements: " << nElementsEsperat[i] << ", Max elements: " << maxElementsEsperat[i] << endl;
		bool resultat = v.elimina(posicio[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultat, outputParcial);
		outputParcial << ", N. elements: " << v.getNElements() << ", Max elements: " << v.getMaxElements() << endl;
		outputParcial << "-----------" << endl;
		if ((resultat == resultatEsperat[i]) && (v.getNElements() == nElementsEsperat[i]) && (v.getMaxElements() == maxElementsEsperat[i]))
		{
			outputParcial << "CORRECTE" << endl;
			outputTest["status"] = "passed";
			grade += 0.2;
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
		cout << endl << "Grade :=>> " << grade << endl << endl;

	}
}



void testOperadorAssignacio(json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	Vector vOriginal, vResultat;

	const int N_ELEMENTS = 12;
	Punt valors[N_ELEMENTS] = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 },{ 11,11 },{ 12,12 } };

	json outputTest =
	{
		{"name", "TEST OPERADOR ASSIGNACIO"},
		{"visibility", "visible"},
		{"output", ""}
	};
	outputParcial << "TEST DE L'OPERADOR D'ASSIGNACIO" << endl;
	outputParcial << "-------------------------------" << endl;
	outputParcial << "" << endl;
	outputParcial << "Inicialitzant el vector original amb valors:" << endl;
	outputParcial << "-----------" << endl;
	mostraArray(valors, N_ELEMENTS, outputParcial);
	for (int i = 0; i < N_ELEMENTS; i++)
		vOriginal.insereix(valors[i], i);
	outputParcial << "-----------" << endl;

	outputParcial << "Copiant el vector amb l'operador d'assignacio:" << endl;
	vResultat = vOriginal;
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut final del vector esperat: " << endl;
	mostraArray(valors, N_ELEMENTS, outputParcial);
	outputParcial << "-----------" << endl;
	outputParcial << "Contingut final del vector copiat amb l'operador d'assignacio: " << endl;
	mostraVector(vResultat, N_ELEMENTS, outputParcial);
	if (comparaVector(vResultat, valors, N_ELEMENTS))
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
	cout << endl << "Grade :=>> " << grade << endl << endl;
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

	cout << endl << "Grade :=>> " << grade << endl << endl;

	Vector v;

	testInsereix(v, output);
	testElimina(v, output);
	testOperadorAssignacio(output);

	grade = output["score"];

	if (grade < 0)
		grade = 0.0;
	cout << "------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}