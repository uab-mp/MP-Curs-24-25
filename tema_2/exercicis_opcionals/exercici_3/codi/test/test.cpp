#include "../source/llista_doble.h"
#include <signal.h>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using json = nlohmann::json;


typedef void(*SignalHandlerPointer)(int);

void SignalHandler(int signal)
{
	if (signal == SIGSEGV) {
		throw "Segmentation fault";
	}
	else 
	{
		throw "Other Error";
	}
}



void escriuValors(int valors[], int nValors, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < nValors-1; i++)
	{
		outputParcial << valors[i] << ",";
	}
	if (nValors > 0)
		outputParcial << valors[nValors - 1];
	outputParcial << "]";
}

void escriuValorsLlista(LlistaDoble& l, stringstream& outputParcial)
{
	outputParcial << "[";
	Node* aux = l.begin();
	int i = 0;
	if (aux != NULL)
	{
		outputParcial << aux->getValor();
		aux = aux->getNext();
	}
	while (aux != NULL)
	{
		outputParcial << "," << aux->getValor();
		aux = aux->getNext();
	}
	outputParcial << "]";
}

void creaLlista(LlistaDoble& l, int valors[], int nValors)
{
	Node* aux = NULL;
	for (int i = nValors-1; i >=0; i--)
		aux = l.insert(valors[i], aux);
}

void destrueixLlista(LlistaDoble& l)
{
	while (l.begin()!=NULL)
	{
		l.erase(l.begin());
	}
}

bool comparaLlista(LlistaDoble& l, int valors[], int nValors)
{
	bool iguals = true;
	Node* aux = l.begin();
	int i = 0;
	while (iguals && (aux != NULL) && (i < nValors))
	{
		if (aux->getValor() != valors[i])
			iguals = false;
		else
		{
			aux = aux->getNext();
			i++;
		}
	}
	iguals = iguals && (aux == NULL) && (i == nValors);
	aux = l.rbegin();
	i = nValors - 1;
	while (iguals && (aux != NULL) && (i >= 0))
	{
		if (aux->getValor() != valors[i])
			iguals = false;
		else
		{
			aux = aux->getPrev();
			i--;
		}
	}
	return (iguals && (aux == NULL) && (i == -1));
}

Node* getPosicioLlista(LlistaDoble& l, int posicio)
{
	Node* nodePosicio = NULL;
	Node* aux = l.begin();
	for (int i = 0; i < posicio; i++)
	{
		nodePosicio = aux;
		aux = aux->getNext();
	}
	return nodePosicio;
}

void testInsereix(json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int N_PROVES = 8;
	const int MAX_ELEMENTS = 4;

	int valorsLlista[N_PROVES][MAX_ELEMENTS] = 
	{ 
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0 },
		{ 0 },
		{} 
	};
	int nValorsLlista[N_PROVES] = { 4, 4, 4, 4, 4, 1, 1, 0 };
	int posicioInserir[N_PROVES] = { 1, 2, 3, 4, 0, 1, 0, 0 };
	int valorInserir = 1;
	int resultatLlista[N_PROVES][MAX_ELEMENTS+1] = 
	{ 
		{ 1, 0, 2, 4, 6 },
		{ 0, 1, 2, 4, 6 },
		{ 0, 2, 1, 4, 6 },
		{ 0, 2, 4, 1, 6 },
		{ 0, 2, 4, 6, 1 },
		{ 1, 0 },
		{ 0, 1 },
		{ 1 } 
	};
	int nValorsResultat[N_PROVES] = { 5, 5, 5, 5, 5, 2, 2, 1 };

	for (int i = 0; i < N_PROVES; i++)
	{
		LlistaDoble l;

		json outputTest =
		{
			{"name", "TEST INSEREIX " + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST INSEREIX " << i + 1 << endl;
		outputParcial << "---------------" << endl;

		outputParcial << "Creant Llista inicial................ " << endl;
		outputParcial << "Valors de la llista inicial: ";  escriuValors(valorsLlista[i], nValorsLlista[i], outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;
		try
		{ 
			creaLlista(l, valorsLlista[i], nValorsLlista[i]);

			outputParcial << "Afegint element....................... " << endl;
			outputParcial << "Valor a inserir: " << valorInserir << endl;
			outputParcial << "Posicio on inserir: " << posicioInserir[i] << endl;
			outputParcial << "------" << endl;
			outputParcial << "Valors esperats de la llista final: "; escriuValors(resultatLlista[i], nValorsResultat[i], outputParcial); outputParcial << endl;
			outputParcial << "------" << endl;

			Node* posicio = getPosicioLlista(l, posicioInserir[i]);
			l.insert(valorInserir, posicio);
			outputParcial << "Valors obtinguts de la llista final: "; escriuValorsLlista(l, outputParcial); outputParcial << endl;
			outputParcial << "------" << endl;

			bool valid = comparaLlista(l, resultatLlista[i], nValorsResultat[i]);

			if (valid)
			{
				outputParcial << "CORRECTE" << endl;
				outputTest["status"] = "passed";
				grade += 0.3;
			}
			else
			{
				outputParcial << "ERROR" << endl;
				outputTest["status"] = "failed";
			}
		}
		catch (const char *e)
		{
			outputParcial << "ERROR d'execucio: " << e << endl;
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


void testElimina(json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int N_PROVES = 8;
	const int MAX_ELEMENTS = 4;
	int valorsLlista[N_PROVES][MAX_ELEMENTS] = 
	{ 
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6 },
		{ 0 },
		{ 0 },
		{} 
	};
	int nValorsLlista[N_PROVES] = { 4, 4, 4, 4, 4, 1, 1, 0 };
	int posicioEliminar[N_PROVES] = { 1 , 2, 3, 4, 0, 1, 0, 0 };
	int resultatLlista[N_PROVES][4] = { 
		{ 2, 4, 6 },
		{ 0, 4, 6 },
		{ 0, 2, 6 },
		{ 0, 2, 4 },
		{ 0, 2, 4, 6 },
		{},
		{ 0 },
		{} 
	};
	int nValorsResultat[N_PROVES] = { 3, 3, 3, 3, 4, 0, 1, 0 };

	for (int i = 0; i < N_PROVES; i++)
	{
		LlistaDoble l;

		json outputTest =
		{
			{"name", "TEST ELIMINA " + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST ELIMINA " << i + 1 << endl;
		outputParcial << "--------------" << endl;

		outputParcial << "Creant Llista inicial................ " << endl;
		outputParcial << "Valors de la llista inicial: ";  escriuValors(valorsLlista[i], nValorsLlista[i], outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;
		try
		{
			creaLlista(l, valorsLlista[i], nValorsLlista[i]);

			outputParcial << "Eliminant element....................... " << endl;
			outputParcial << "Posicio de l'element a eliminar: " << posicioEliminar[i] << endl;
			outputParcial << "------" << endl;
			outputParcial << "Valors esperats de la llista final: "; escriuValors(resultatLlista[i], nValorsResultat[i], outputParcial); outputParcial << endl;
			outputParcial << "------" << endl;

			Node *posicio = getPosicioLlista(l, posicioEliminar[i]);
			l.erase(posicio);

			outputParcial << "Valors obtinguts de la llista final: "; escriuValorsLlista(l, outputParcial); outputParcial << endl;
			outputParcial << "------" << endl;

			bool valid = comparaLlista(l, resultatLlista[i], nValorsResultat[i]);
			outputParcial << "------" << endl;

			if (valid)
			{
				outputParcial << "CORRECTE" << endl;
				outputTest["status"] = "passed";
				grade += 0.3;
			}
			else
			{
				outputParcial << "ERROR" << endl;
				outputTest["status"] = "failed";
			}
		}
		catch (const char *e)
		{
			outputParcial << "ERROR d'execucio: " << e << endl;
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

void testUnique(json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int N_PROVES = 8;
	const int MAX_ELEMENTS = 6;
	int valorsLlista[N_PROVES][MAX_ELEMENTS] =
	{
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6, 2 },
		{ 2, 2, 4, 6 },
		{ 2, 2, 2, 2 },
		{ 0, 2, 2, 4 },
		{ 0 },
		{ 0, 2, 2, 4, 6, 6 },
		{}
	};
	int nValorsLlista[N_PROVES] = { 4, 5, 4, 4, 4, 1, 6, 0 };
	int resultatLlista[N_PROVES][MAX_ELEMENTS] = 
	{
		{ 0, 2, 4, 6 },
		{ 0, 2, 4, 6, 2},
		{ 2, 4, 6 },
		{ 2},
		{ 0, 2, 4},
		{ 0 },
		{ 0, 2, 4, 6 },
		{}
	};
	int nValorsResultat[N_PROVES] = { 4, 5, 3, 1, 3, 1, 4, 0 };

	for (int i = 0; i < N_PROVES; i++)
	{
		LlistaDoble l;

		json outputTest =
		{
			{"name", "TEST UNIQUE " + to_string(i + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST UNIQUE " << i + 1 << endl;
		outputParcial << "---------------" << endl;

		outputParcial << "Creant Llista inicial................ "  << endl;
		outputParcial << "Valors de la llista inicial: ";  escriuValors(valorsLlista[i], nValorsLlista[i], outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;
		try
		{
			creaLlista(l, valorsLlista[i], nValorsLlista[i]);

			outputParcial << "Eliminant elements duplicats consecutius....................... " << endl;
			outputParcial << "------" << endl;
			outputParcial << "Valors esperats de la llista final: "; escriuValors(resultatLlista[i], nValorsResultat[i], outputParcial); outputParcial << endl;
			outputParcial << "------" << endl;

			l.unique();

			outputParcial << "Valors obtinguts de la llista final: "; escriuValorsLlista(l, outputParcial); outputParcial << endl;
			outputParcial << "------" << endl;

			bool valid = comparaLlista(l, resultatLlista[i], nValorsResultat[i]);

			if (valid)
			{
				outputParcial << "CORRECTE" << endl;
				outputTest["status"] = "passed";
				grade += 0.3;
			}
			else
			{
				outputParcial << "ERROR" << endl;
				outputTest["status"] = "failed";
			}

		}
		catch (const char *e)
		{
			outputParcial << "ERROR d'execucio: " << e << endl;
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

	const int MAX_ELEMENTS = 4;
	int valorsLlista[MAX_ELEMENTS] = { 0, 2, 4, 6 };
	int nValorsLlista = 4;

	json outputTest =
	{
		{"name", "TEST OPERADOR ASSIGNACIO"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST OPERADOR ASSIGNACIO" << endl;
	outputParcial << "------------------------" << endl;
	LlistaDoble l1, l2;
	outputParcial << "Creant Llista inicial................ " << endl;
	outputParcial << "Valors de la llista inicial: ";  escriuValors(valorsLlista, nValorsLlista, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	try
	{
		creaLlista(l1, valorsLlista, nValorsLlista);
		outputParcial << "Fent copia de la llista inicial amb operador assignacio................ " << endl;
		l2 = l1;
		outputParcial << "------" << endl;
		outputParcial << "Destruint llista inicial................ " << endl;
		destrueixLlista(l1);
		outputParcial << "Valors la llista obtinguda amb la copia: ";  escriuValorsLlista(l2, outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;

		bool valid = comparaLlista(l2, valorsLlista, nValorsLlista);

		if (valid)
		{
			outputParcial << "CORRECTE" << endl;
			outputTest["status"] = "passed";
			grade += 2.8;
		}
		else
		{
			outputParcial << "ERROR" << endl;
			outputTest["status"] = "failed";
		}
	}
	catch (const char *e)
	{
		outputParcial << "ERROR d'execucio: " << e << endl;
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

	SignalHandlerPointer previousHandler;
	previousHandler = signal(SIGSEGV, SignalHandler); //SIGSEGV Illegal storage access

	testInsereix(output);	
	testElimina(output);
	testUnique(output);
	testOperadorAssignacio(output);

	grade = output["score"];

	if (grade < 0)
		grade = 0.0;
	cout << "------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}