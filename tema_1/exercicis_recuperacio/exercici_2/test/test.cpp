#include "../source/llista.h"
#include "json.hpp"
#include <string>
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

bool comparaLlistes(Llista& l, Estudiant* resultat, int longitud)
{
	bool iguals = (longitud == l.getNumElements());
	if (iguals)
	{
		int i = 0;
		while ((i < longitud) && iguals)
		{
			Estudiant estudiant = l.getElement(i);
			if (!((resultat[i].getNom() == estudiant.getNom()) && 
				(resultat[i].getNiu() == estudiant.getNiu()) &&
				(resultat[i].calculaNotaMitjana() == estudiant.calculaNotaMitjana())))
				iguals = false;
			else
				i++;
		}
	}
	return iguals;
}

void mostraVector(Estudiant v[], int mida, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < mida - 1; i++)
	{
		outputParcial << "[" << v[i].getNom() << "," << v[i].getNiu() << "," << v[i].calculaNotaMitjana() << "]" << ", ";
	}
	if (mida > 0)
		outputParcial << "[" << v[mida - 1].getNom() << "," << v[mida - 1].getNiu() << "," << v[mida - 1].calculaNotaMitjana() << "]";
	outputParcial << "]";
}

void mostraLlista(Llista& l, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < l.getNumElements() - 1; i++)
	{
		Estudiant e = l.getElement(i);
		outputParcial << "[" << e.getNom() << "," << e.getNiu() << "," << e.calculaNotaMitjana() << "]" << ", ";
	}
	if (l.getNumElements() > 0)
	{
		Estudiant e = l.getElement(l.getNumElements() - 1);
		outputParcial << "[" << e.getNom() << "," << e.getNiu() << "," << e.calculaNotaMitjana() << "]";

	}
	outputParcial << "]";
}

void mostraBuffer(stringstream& buffer, stringstream& outputParcial)
{
	string stringData;
	getline(buffer, stringData);
	while (stringData != "")
	{
		outputParcial << stringData << endl;
		getline(buffer, stringData);
	}
}

float testInicialitzacioLlista(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST INICIALITZACIO LLISTA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test de la inicialitzacio de la classe Llista" << endl;
	outputParcial << "======================================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	const int N_ELEMENTS = 5;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"},
		{ "NOM_5", "NIU_5"}
	};
	float notesTest[N_ELEMENTS] = { 5, 6, 7, 8, 9 };
	for (int i = 0; i < N_ELEMENTS; i++)
		estudiantTest[i].afegeixNota(notesTest[i]);

	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << "----------" << endl;
	outputParcial << "Contingut de la llista despres d'inicialitzar (fa servir metodes getElement i getNumElements): " << endl;

	outputParcial << "";  mostraLlista(l, outputParcial); outputParcial << endl;

	outputParcial << "----------" << endl;
	bool iguals = comparaLlistes(l, estudiantTest, N_ELEMENTS);
	outputParcial << "Comprovant si contingut correcte (fa servir metodes getElement i getNumElements)... " << endl;
	if (!iguals)
	{
		outputParcial << "ERROR" << endl;
		reduccio += 1.0;
	}
	else
		outputParcial << "CORRECTE" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	return reduccio;
}

float testPertany(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST PERTANY"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test del metode pertany" << endl;
	outputParcial << "================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	const int N_ELEMENTS = 5;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"},
		{ "NOM_5", "NIU_5"}
	};
	float notesTest[N_ELEMENTS] = { 5, 6, 7, 8, 9 };
	for (int i = 0; i < N_ELEMENTS; i++)
		estudiantTest[i].afegeixNota(notesTest[i]);

	const int N_PROVES = 5;
	Estudiant estudiantTestPertany[N_PROVES] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_5", "NIU_5"},
		{ "NOM_1", "NIU_5"},
		{ "NOM_5", "NIU_1"}
	};
	bool resultatEsperat[N_PROVES] = { true, true, true, false, false };

	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << endl;
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Estudiant a buscar dins la llista: " << estudiantTestPertany[i].getNom() << ", " << estudiantTestPertany[i].getNiu() << endl;
		outputParcial << "---" << endl;
		outputParcial << "Valor retorn esperat: " ; mostraBool(resultatEsperat[i], outputParcial); outputParcial <<  endl;
		outputParcial << "---" << endl;
		bool resultat = l.pertany(estudiantTestPertany[i]);
		outputParcial << "Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		if (resultat == resultatEsperat[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}

float testCerca(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CERCA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test del metode cerca" << endl;
	outputParcial << "==============================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	const int N_ELEMENTS = 5;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"},
		{ "NOM_5", "NIU_5"}
	};

	const int N_PROVES = 4;
	string estudiantTestPertany[N_PROVES] = { "NIU_1", "NIU_3", "NIU_5", "NIU_6"};
	int resultatEsperat[N_PROVES] = { 0, 2, 4, -1};

	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << endl;
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Cerca de l'estudiant amb niu: " << estudiantTestPertany[i] << endl;
		outputParcial << "---" << endl;
		outputParcial << "Valor retorn esperat: " << resultatEsperat[i] << endl;
		outputParcial << "---" << endl;
		int resultat = l.cerca(estudiantTestPertany[i]);
		outputParcial << "Valor retorn obtingut: " << resultat << endl;
		if (resultat == resultatEsperat[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}

float testGetElement(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST GET ELEMENT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test del metode getElement" << endl;
	outputParcial << "===================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	const int N_ELEMENTS = 5;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"},
		{ "NOM_5", "NIU_5"}
	};
	float notesTest[N_ELEMENTS] = { 5, 6, 7, 8, 9 };
	for (int i = 0; i < N_ELEMENTS; i++)
		estudiantTest[i].afegeixNota(notesTest[i]);

	const int N_PROVES = 5;
	int posicio[N_PROVES] = { 0, 2, 4, -1, 5 };
	Estudiant resultatEsperat[N_PROVES] = 
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_5", "NIU_5"},
		{ "", ""},
		{ "", ""}
	};
	float notaEsperada[N_PROVES] = { 5, 7, 9, -1, -1 };
	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << endl;
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Posicio de la llista a retornar: " << posicio[i] << endl;
		outputParcial << "---" << endl;
		outputParcial << "Valor retorn esperat: " << resultatEsperat[i].getNom() << ", " << resultatEsperat[i].getNiu() << ", " << notaEsperada[i] << endl;
		outputParcial << "---" << endl;
		Estudiant resultat = l.getElement(posicio[i]);
		outputParcial << "Valor retorn obtingut: " << resultat.getNom() << ", " << resultat.getNiu() << ", " << resultat.calculaNotaMitjana() << endl;
		if (((resultat.getNom() == resultatEsperat[i].getNom()) &&
			(resultat.getNiu() == resultatEsperat[i].getNiu()) &&
			(resultat.calculaNotaMitjana() == notaEsperada[i])))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}


float testOperadorSuma(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST SUMA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test operador +" << endl;
	outputParcial << "========================" << endl;
	outputParcial << "Inicialitzant la llista buida (amb el constructor per defecte): " << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l;

	const int N_PROVES = 4;
	const int N_ELEMENTS = 4;
	Estudiant estudiantTest[N_PROVES] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"}
	};
	Estudiant resultatEsperat[N_PROVES][N_ELEMENTS] =
	{
		{
			{ "NOM_1", "NIU_1"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"},
			{ "NOM_3", "NIU_3"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		}
	};
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Estudiant a afegir: " << estudiantTest[i].getNom() << ", " << estudiantTest[i].getNiu() << endl;
		outputParcial << "---" << endl;
		bool resultat = l + estudiantTest[i];
		outputParcial << "Llista resultat esperada: " << endl;
		outputParcial << ""; mostraVector(resultatEsperat[i], i + 1, outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(true, outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Llista resultat obtinguda: " << endl;
			outputParcial << "";  mostraLlista(l, outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		bool iguals = comparaLlistes(l, resultatEsperat[i], i + 1);
		outputParcial << "Comprovant si contingut correcte ... " << endl;
		if (iguals && resultat)
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Afegint elements fins a omplir la llista ..." << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = N_PROVES; i < 100; i++)
		bool resultat = l + estudiantTest[0];
	outputParcial << "----------" << endl;
	outputParcial << "Afegint un element a la llista plena ..." << endl;
	bool resultat = l + estudiantTest[0];
	outputParcial << "Valor retorn esperat: "; mostraBool(false, outputParcial); outputParcial << endl;
	outputParcial << "----------" << endl;
	outputParcial << "Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
	outputParcial << "----------" << endl;
	if (!resultat)
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 0.5;
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}

float testOperadorResta(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST RESTA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test operador -" << endl;
	outputParcial << "========================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_PROVES = 7;
	const int N_ELEMENTS = 4;

	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"}
	};
	Estudiant estudiantEliminar[N_PROVES] = 
	{
		{ "NOM_5", "NIU_5"}, 
		{ "NOM_2", "NIU_2"},
		{ "NOM_1", "NIU_1"},
		{ "NOM_1", "NIU_1"},
		{ "NOM_4", "NIU_4"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_3", "NIU_3"}
	};
	Estudiant llistaEsperada[N_PROVES][N_ELEMENTS] =
	{
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}		
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		},
		{
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		},
		{
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		},
		{
			{ "NOM_3", "NIU_3"},
		},
		{
		},
		{
		}
	};
	bool resultatEsperat[N_PROVES] = { false, true, true, false, true, true, false };
	int nElementsEsperats[N_PROVES] = { 4, 3, 2, 2, 1, 0, 0 };
	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Estudiant a eliminar: " << estudiantEliminar[i].getNom() << ", " << estudiantEliminar[i].getNiu() << endl;
		outputParcial << "----------" << endl;
		bool resultat = l - estudiantEliminar[i];
		outputParcial << "Llista resultat esperada: " << endl;
		outputParcial << ""; mostraVector(llistaEsperada[i], nElementsEsperats[i], outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Llista resultat obtinguda: " << endl;
			outputParcial << "";  mostraLlista(l, outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		bool iguals = comparaLlistes(l, llistaEsperada[i], nElementsEsperats[i]);
		outputParcial << "Comprovant si contingut correcte ... " << endl;
		if (iguals && (resultat == resultatEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}


float testInsereix(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST INSEREIX"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test metode insereix" << endl;
	outputParcial << "=============================" << endl;
	outputParcial << "Inicialitzant la llista buida (amb el constructor per defecte): " << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l;

	const int N_PROVES = 7;
	const int N_ELEMENTS = 5;
	Estudiant estudiantTest[N_PROVES] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"},
		{ "NOM_5", "NIU_5"}
	};
	int posicioTest[N_PROVES] = { 0, 1, 3, -1, 1, 1, 0 };
	Estudiant llistaEsperada[N_PROVES][N_ELEMENTS] =
	{
		{
			{ "NOM_1", "NIU_1"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_2", "NIU_2"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_4", "NIU_4"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_2", "NIU_2"}
		},
		{
			{ "NOM_5", "NIU_5"},
			{ "NOM_1", "NIU_1"},
			{ "NOM_4", "NIU_4"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_2", "NIU_2"}
		}
	};
	bool resultatEsperat[N_PROVES] = { true, true, false, false, true, true, true };
	int nElementsEsperats[N_PROVES] = { 1, 2, 2, 2, 3, 4, 5 };
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Estudiant a afegir: " << estudiantTest[i] << endl;
		outputParcial << "Posicio: " << posicioTest[i] << endl;
		outputParcial << "---" << endl;
		bool resultat = l.insereix(estudiantTest[i], posicioTest[i]);
		outputParcial << "Llista resultat esperada: " << endl;
		outputParcial << ""; mostraVector(llistaEsperada[i], nElementsEsperats[i], outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Llista resultat obtinguda: " << endl;
			outputParcial << "";  mostraLlista(l, outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		bool iguals = comparaLlistes(l, llistaEsperada[i], nElementsEsperats[i]);
		outputParcial << "Comprovant si contingut correcte ... " << endl;
		if (iguals && (resultat == resultatEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Afegint elements fins a omplir la llista ..." << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 5; i < 100; i++)
		bool resultat = l.insereix(estudiantTest[0], 0);
	outputParcial << "----------" << endl;
	outputParcial << "Afegint un element a la llista plena ..." << endl;
	bool resultat = l.insereix(estudiantTest[0], 0);
	outputParcial << "Valor retorn esperat: "; mostraBool(false, outputParcial); outputParcial << endl;
	outputParcial << "----------" << endl;
	outputParcial << "Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
	outputParcial << "----------" << endl;
	if (!resultat)
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 0.5;
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}

float testElimina(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST ELIMINA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test metode elimina" << endl;
	outputParcial << "============================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_PROVES = 7;
	const int N_ELEMENTS = 4;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"}
	};
	int posicioEliminar[N_PROVES] = { -1, 1, 3, 0, 1, 0, 1 };
	Estudiant llistaEsperada[N_PROVES][N_ELEMENTS] =
	{
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_2", "NIU_2"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		},
		{
			{ "NOM_1", "NIU_1"},
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		},
		{
			{ "NOM_3", "NIU_3"},
			{ "NOM_4", "NIU_4"}
		},
		{
			{ "NOM_3", "NIU_3"},
		},
		{
		},
		{
		}
	};
	bool resultatEsperat[N_PROVES] = { false, true, false, true, true, true, false };
	int nElementsEsperats[N_PROVES] = { 4, 3, 3, 2, 1, 0, 0 };
	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Posicio a eliminar: " << posicioEliminar[i] << endl;
		outputParcial << "----------" << endl;
		bool resultat = l.elimina(posicioEliminar[i]);
		outputParcial << "Llista resultat esperada: " << endl;
		outputParcial << ""; mostraVector(llistaEsperada[i], nElementsEsperats[i], outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Llista resultat obtinguda: " << endl;
			outputParcial << "";  mostraLlista(l, outputParcial); outputParcial << endl;
		outputParcial << "Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		bool iguals = comparaLlistes(l, llistaEsperada[i], nElementsEsperats[i]);
		outputParcial << "Comprovant si contingut correcte ... " << endl;
		if (iguals && (resultat == resultatEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}

float testSortidaPantalla(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST SORTIDA PANTALLA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test operador << de sortida a pantalla" << endl;
	outputParcial << "===============================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_ELEMENTS = 4;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"}
	};
	float notesTest[N_ELEMENTS] = { 5, 6, 7, 8};
	for (int i = 0; i < N_ELEMENTS; i++)
		estudiantTest[i].afegeixNota(notesTest[i]);

	string resultatEsperat[N_ELEMENTS] = { "NOM_1 NIU_1 5", "NOM_2 NIU_2 6", "NOM_3 NIU_3 7", "NOM_4 NIU_4 8"};

	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	outputParcial << "Escrivint la llista a la sortida estandard amb outputParcial ...." << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	ofstream fitxerTestOut;
	string nomFitxerOut = "test_llista_outputParcial.txt";
	fitxerTestOut.open(nomFitxerOut);
	streambuf* buffer_outputParcial = cout.rdbuf(fitxerTestOut.rdbuf());
	cout << l;
	cout.rdbuf(buffer_outputParcial);
	fitxerTestOut.close();

	outputParcial << "-----" << endl;
	outputParcial << "Resultat esperat: " << endl;
	for (int i = 0; i < N_ELEMENTS; i++)
		outputParcial << resultatEsperat[i] << endl;

	ifstream fitxerTestResultat;
	fitxerTestResultat.open(nomFitxerOut);
	string resultat;
	outputParcial << "-----" << endl;
	outputParcial << "Resultat obtingut: " << endl;
	bool error = false;
	for (int i = 0; i < N_ELEMENTS; i++)
	{
		getline(fitxerTestResultat, resultat);
		outputParcial << resultat << endl;
		if (resultat != resultatEsperat[i])
			error = true;
	}
	fitxerTestResultat.close();

	if (!error)
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 0.5;
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 0.5)
		reduccio = 0.5;
	return reduccio;
}


float testSortidaFitxer(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST SORTIDA FITXER"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test operador << de escriptura a fitxer" << endl;
	outputParcial << "================================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_ELEMENTS = 4;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"}
	};
	float notesTest[N_ELEMENTS] = { 5, 6, 7, 8 };
	for (int i = 0; i < N_ELEMENTS; i++)
		estudiantTest[i].afegeixNota(notesTest[i]);

	string resultatEsperat[N_ELEMENTS] = { "NOM_1 NIU_1 5", "NOM_2 NIU_2 6", "NOM_3 NIU_3 7", "NOM_4 NIU_4 8" };

	outputParcial << "Inicialitzant la llista amb valors: " << endl;
	outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l(estudiantTest, N_ELEMENTS);
	outputParcial << endl;

	outputParcial << "Escrivint la llista al fitxer amb l'operador << ...." << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	ofstream fitxerTestOut;
	string nomFitxerOut = "test_llista_fitxer.txt";
	fitxerTestOut.open(nomFitxerOut);
	if (fitxerTestOut.is_open())
	{
		fitxerTestOut << l;
		fitxerTestOut.close();

		outputParcial << "-----" << endl;
		outputParcial << "Resultat esperat: " << endl;
		for (int i = 0; i < N_ELEMENTS; i++)
			outputParcial << resultatEsperat[i] << endl;

		ifstream fitxerTestResultat;
		fitxerTestResultat.open(nomFitxerOut);
		string resultat;
		outputParcial << "-----" << endl;
		outputParcial << "Resultat obtingut: " << endl;
		bool error = false;
		for (int i = 0; i < N_ELEMENTS; i++)
		{
			getline(fitxerTestResultat, resultat);
			outputParcial << resultat << endl;
			if (resultat != resultatEsperat[i])
				error = true;
		}
		fitxerTestResultat.close();
		if (!error)
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
	}
	else
	{
		outputParcial << "ERROR OBRINT EL FITXER" << endl;
		reduccio += 0.5;
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 0.5)
		reduccio = 0.5;
	return reduccio;
}

float testLecturaFitxer(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST LECTURA FITXER"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << endl;
	outputParcial << "Iniciant test operador >> de lectura de fitxer" << endl;
	outputParcial << "==============================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_ELEMENTS = 4;
	Estudiant estudiantTest[N_ELEMENTS] =
	{
		{ "NOM_1", "NIU_1"},
		{ "NOM_2", "NIU_2"},
		{ "NOM_3", "NIU_3"},
		{ "NOM_4", "NIU_4"}
	};
	int nNotesTest[N_ELEMENTS] = { 1, 0, 2, 3 };
	float notesTest[N_ELEMENTS][MAX_NOTES] = 
	{
		{ 5 },
		{ },
		{6, 8 },
		{5, 7, 9}
	};
	for (int i = 0; i < N_ELEMENTS; i++)
		for (int j = 0; j < nNotesTest[i]; j++)
			estudiantTest[i].afegeixNota(notesTest[i][j]);

	outputParcial << "Llegint la llista del fitxer amb l'operador >> .... " << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	Llista l;

	ifstream fitxerTestIn;
	string nomFitxerIn = "test_llista_fitxer_in.txt";
	fitxerTestIn.open(nomFitxerIn);
	if (fitxerTestIn.is_open())
	{
		fitxerTestIn >> l;
		fitxerTestIn.close();

		outputParcial << endl;
		outputParcial << "Contingut esperat de la llista: " << endl;
		outputParcial << ""; mostraVector(estudiantTest, N_ELEMENTS, outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Contingut de la llista despres llegir del fitxer: " << endl;
			outputParcial << "";  mostraLlista(l, outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		bool iguals = comparaLlistes(l, estudiantTest, N_ELEMENTS);
		outputParcial << "Comprovant si contingut correcte ... " << endl;
		if (!iguals)
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		else
			outputParcial << "CORRECTE" << endl;

	}
	else
	{
		outputParcial << "ERROR OBRINT EL FITXER" << endl;
		reduccio += 1.0;
	}

	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");


	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}




int main()
{
	float grade = 0.0;
	float reduccio;

	json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
	output["stdout_visibility"] = "visible";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestInicialitza;
	reduccio = testInicialitzacioLlista(outputTestInicialitza);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestInicialitza);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestPertany;
	reduccio = testPertany(outputTestPertany);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestPertany);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestCerca;
	reduccio = testCerca(outputTestCerca);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestCerca);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestGetElement;
	reduccio = testGetElement(outputTestGetElement);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestGetElement);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestOperadorSuma;
	reduccio = testOperadorSuma(outputTestOperadorSuma);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestOperadorSuma);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestOperadorResta;
	reduccio = testOperadorResta(outputTestOperadorResta);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestOperadorResta);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestInsereix;
	reduccio = testInsereix(outputTestInsereix);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestInsereix);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestElimina;
	reduccio = testElimina(outputTestElimina);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestElimina);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestSortida;
	reduccio = testSortidaPantalla(outputTestSortida);
	grade = grade + (0.5 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestSortida);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestSortidaFitxer;
	reduccio = testSortidaFitxer(outputTestSortidaFitxer);
	grade = grade + (0.5 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestSortidaFitxer);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestLecturaFitxer;
	reduccio = testLecturaFitxer(outputTestLecturaFitxer);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestLecturaFitxer);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();


	if (grade < 0)
		grade = 0.0;
	cout << "Grade :=>> " << grade << endl;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	return 0;

}