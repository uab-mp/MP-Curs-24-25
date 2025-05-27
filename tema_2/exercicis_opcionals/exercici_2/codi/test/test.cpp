#include "../source/llista.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using json = nlohmann::json;

#include <signal.h>
typedef void(*SignalHandlerPointer)(int);
void SignalHandler(int signal)
{
	if (signal == SIGSEGV) {
		throw "Segmentation fault";
	}
	else {
		throw "Other Error";
	}
}
SignalHandlerPointer previousHandler;

ostream& operator<<(ostream& out, const Punt& pt)
{
	out << "(" << pt.getX() << "," << pt.getY() << ")";
	return out;
}

void escriuLlista(Llista &l, stringstream& outputParcial)
{
	try
	{
		Node *aux = l.getInici();
		outputParcial << " [ ";
		while (aux != NULL)
		{
			outputParcial << aux->getValor();
			aux = aux->getNext();
			if (aux != NULL) outputParcial << ",";
		}
		outputParcial << " ]" << endl;
	}
	catch (const char *e)
	{
		outputParcial << "ERROR EXECUCIO a l'escriure la llista: " << e << endl;
		throw e;
	}
}

void escriuVector(Punt v[],int mida, stringstream& outputParcial)
{
	outputParcial << " [ ";
	for (int i = 0; i < mida; i++)
	{
		outputParcial << v[i];		
		if (i != mida-1) outputParcial << ",";
	}		
	outputParcial << " ]" << endl;
}

void creaLlista(Llista &l, Punt valors[], int nValors, stringstream& outputParcial)
{
	try
	{
		Node *aux = NULL;
		for (int i = 0; i < nValors; i++)
		{
			aux = l.insereix(valors[i], aux);
		}
	}
	catch (const char *e)
	{
		outputParcial << "ERROR EXECUCIO al crear la llista: " << e << endl;
		throw e;
	}
}

void destrueixLlista(Llista &l, stringstream& outputParcial)
{
	try
	{
		if (!l.esBuida())
		{
			while (l.elimina(nullptr) != nullptr);
		}
	}
	catch (const char *e)
	{
		outputParcial << "ERROR EXECUCIO al destruir la llista: " << e << endl;
		throw e;
	}
}

bool comparaLlista(Llista &l, Punt valors[], int nValors, stringstream& outputParcial)
{
	try
	{
		bool iguals = true;
		Node *aux = l.getInici();
		int i = 0;

		while (iguals && (aux != NULL))
		{
			if (!(aux->getValor() == valors[i]))
				iguals = false;
			else
			{
				aux = aux->getNext();
				i++;
			}
		}
		return (iguals && (aux == NULL) && (i == nValors));
	}
	catch (const char *e)
	{
		outputParcial << "ERROR EXECUCIO al comparar la llista: " << e << endl;
		throw e;
	}	
}

Node* pos2Node(Llista& l, int posicio)
{
	Node* pos = nullptr;
	Node* aux = l.getInici();
	int i = 0;
	while ((i < posicio) and (aux != nullptr))
	{
		i++;
		pos = aux;
		aux = aux->getNext();
	}
	return pos;
}

void testInsereix(Llista& l, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int MAX_PROVES = 6;

	Punt valors[MAX_PROVES] = { { 2,2 },{ 1,1 },{5,5},{ 3,3 },{4,4}, {6,6} };
	int posicio[MAX_PROVES] = { 0, 0, 2, 2, 3, 5};
	Punt llistaFinal[MAX_PROVES] = { {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6} };

	json outputTest =
	{
		{"name", "TEST INSEREIX "},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST INSEREIX " << endl;
	outputParcial << "-------------" << endl;

	for (int i = 0; i < MAX_PROVES; i++)
	{
		outputParcial << "Afegint punt " << valors[i] << " despres de la posicio " << posicio[i] << endl;
		l.insereix(valors[i], pos2Node(l, posicio[i]));
	}
	outputParcial << "----------" << endl;
	outputParcial << "Contingut final esperat de la llista: " << endl;
	escriuVector(llistaFinal, MAX_PROVES, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Contingut final obtingut de la llista: " << endl;
	escriuLlista(l, outputParcial);
	outputParcial << "----------" << endl;
	if (comparaLlista(l, llistaFinal, MAX_PROVES, outputParcial))
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 4.0;
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


void testElimina(Llista& l, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int MAX_PROVES = 4;
	const int N_ELEMENTS_FINAL = 2;

	int posicio[MAX_PROVES] = { 0, 4, 2, 1};
	Punt llistaFinal[N_ELEMENTS_FINAL] = { {2,2}, {5,5}};

	json outputTest =
	{
		{"name", "TEST ELIMINA "},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST ELIMINA (A partir de la llista creada amb el test INSEREIX)" << endl;
	outputParcial << "----------------------------------------------------------------" << endl;


	for (int i = 0; i < MAX_PROVES; i++)
	{
		outputParcial << "Eliminant punt despres de la posicio " << posicio[i] << endl;
		l.elimina(pos2Node(l, posicio[i]));
	}
	outputParcial << "----------" << endl;
	outputParcial << "Contingut final esperat de la llista: " << endl;
	escriuVector(llistaFinal, N_ELEMENTS_FINAL, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Contingut final obtingut de la llista: " << endl;
	escriuLlista(l, outputParcial);
	outputParcial << "----------" << endl;
	if (comparaLlista(l, llistaFinal, N_ELEMENTS_FINAL, outputParcial))
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 4.0;
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

void testOperadorAssignacio(json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	Llista lOriginal, lResultat;

	const int N_ELEMENTS = 12;
	Punt valors[N_ELEMENTS] = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 },{ 6,6 },{ 7,7 },{ 8,8 },{ 9,9 },{ 10,10 },{ 11,11 },{ 12,12 } };

	json outputTest =
	{
		{"name", "TEST OPERADOR ASSIGNACIO "},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST OPERADOR ASSIGNACIO" << endl;
	outputParcial << "------------------------" << endl;

	outputParcial << "Inicialitzant la llista original amb valors:" << endl;
	escriuVector(valors, N_ELEMENTS, outputParcial);
	for (int i = 0; i < N_ELEMENTS; i++)
		lOriginal.insereix(valors[i], pos2Node(lOriginal, i));
	outputParcial << "----------" << endl;

	outputParcial << "Copiant la llista amb l'operador d'assignacio:" << endl;
	lResultat = lOriginal;
	outputParcial << "----------" << endl;

	outputParcial << "Contingut final esperat de la llista: " << endl;
	escriuVector(valors, N_ELEMENTS, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Contingut final de la llista copiada amb l'operador d'assignacio: " << endl;
	escriuLlista(lResultat, outputParcial);
	outputParcial << "----------" << endl;
	if (comparaLlista(lResultat, valors, N_ELEMENTS, outputParcial))
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
	float grade = 0;
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
	previousHandler = signal(SIGSEGV, SignalHandler); //SIGSEGV Illegal storage access
	
	Llista l;

	testInsereix(l, output); 
	testElimina(l, output);
	testOperadorAssignacio(output);

	grade = output["score"];

	if (grade < 0)
		grade = 0.0;
	if (grade >= 10.0)
	{
		grade = 10;
		cout << "Final del test sense errors" << endl;
	}

	return 0;
}