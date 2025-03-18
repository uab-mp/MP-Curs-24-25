#include "../source/data.h"
#include "../source/gestio_projecte.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;


void escriuData(Data& diaG, stringstream& outputParcial)
{
	outputParcial << diaG.getDia() << "/" << diaG.getMes() << "/" << diaG.getAny();
}

bool igualDies(Data& dia1, Data& dia2)
{
	return ((dia1.getDia() == dia2.getDia()) && (dia1.getMes() == dia2.getMes()) && (dia1.getAny() == dia2.getAny()));
}

void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "TRUE ";
	else
		outputParcial << "FALSE ";
}

float testOperadorsES(json& output)
{
	float reduccio = 0.0;

	Data resultat;
	streambuf* orig = std::cin.rdbuf();
	istringstream input("13\n9\n2014");
	ostringstream outputStr;
	Data resultatEsperat;
	resultatEsperat.setData(13, 9, 2014);

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE DATA: OPERADORS E/S"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test dels operadors d'E/S" << endl;
	outputParcial << "==================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	outputParcial << "Llegint valors de l'entrada" << endl;
	outputParcial << "----------" << endl;
	outputParcial << "Resultat esperat: 13/09/2014" << endl;
	cin.rdbuf(input.rdbuf());
	cin >> resultat;
	cin.rdbuf(orig);
	outputParcial << "----------" << endl;
	outputParcial << "Resultat obtingut: " << resultat << endl;

	outputStr << resultat;

	if (igualDies(resultat, resultatEsperat) && (outputStr.str() == "13/09/2014"))
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 0.25;
	}
	outputParcial << "-----------------------------------------------" << endl;
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


void mostraResultatComparacio(int resultat, stringstream& outputParcial)
{
	switch (resultat)
	{
	case 0:
		outputParcial << "Dates iguals" << endl;
		break;
	case -1:
		outputParcial << "Data 1 < Data 2" << endl;
		break;
	case 1:
		outputParcial << "Data 1 > Data 2" << endl;
		break;
	}
}

float testComparaDates(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 9;
	Data dates1[N_PROVES] = { { 1, 1, 1996 },{ 1, 1, 1900 },{ 2, 1, 1900 },{ 1, 1, 2000 },{ 31, 12, 1999 },{ 1, 1, 1997 },{ 1, 2, 1997 },{ 1, 1, 2006 },{ 1, 1, 2004 } };
	Data dates2[N_PROVES] = { { 1, 1, 1996 },{ 2, 1, 1900 },{ 1, 1, 1900 },{ 31, 12, 1999 },{ 1, 1, 2000 },{ 1, 2, 1997 },{ 1, 1, 1997 },{ 1, 1, 2004 }, { 1, 1, 2006 } };
	int iguals[N_PROVES] = { 0, -1, 1, 1, -1, -1, 1, 1, -1 };

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE DATA: OPERADORS COMPARACIO"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test dels operadors de comparacio" << endl;
	outputParcial << "==========================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data 1: "; escriuData(dates1[i], outputParcial); outputParcial << endl;
		outputParcial << "Data 2: "; escriuData(dates2[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: ";
		mostraResultatComparacio(iguals[i], outputParcial);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: ";
		int resultat = -2;
		if (dates1[i] == dates2[i])
			resultat = 0;
		else
			if (dates1[i] < dates2[i])
				resultat = -1;
			else
				if (!(dates1[i] <= dates2[i]))
				resultat = 1;	
		mostraResultatComparacio(resultat, outputParcial);
		if (resultat == iguals[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.1;
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

	if (reduccio > 0.25)
		reduccio = 0.25;
	return reduccio;
}



float testSumaDies(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 8;
	Data dates[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 20, 12, 2018 },
		{ 10, 1, 2018 }
	};

	int nDies[N_PROVES] = { 0, 1, 21, 31, 59, 90, 31, 365 };

	Data resultatEsperat[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 11, 1, 2018 },
		{ 31, 1, 2018 },
		{ 10, 2, 2018 },
		{ 10, 3, 2018 },
		{ 10, 4, 2018 },
		{ 20, 1, 2019 },
		{ 10, 1, 2019 }
	};

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE DATA: OPERADOR SUMA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de l'operador de suma +" << endl;
	outputParcial << "=====================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data inicial: "; escriuData(dates[i], outputParcial); outputParcial << endl;
		outputParcial << "N. dies a sumar: " << nDies[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; escriuData(resultatEsperat[i], outputParcial); outputParcial << endl;
		Data resultat = dates[i] + nDies[i];
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; escriuData(resultat, outputParcial); outputParcial << endl;
		if (igualDies(resultat, resultatEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	output["output"] = outputFinal;

	if (reduccio > 1.0)
		reduccio = 1.0;
	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	return reduccio;
}

float testIgualSuma(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 8;
	Data dates[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 20, 12, 2018 },
		{ 10, 1, 2018 }
	};

	int nDies[N_PROVES] = { 0, 1, 21, 31, 59, 90, 31, 365 };

	Data resultatEsperat[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 11, 1, 2018 },
		{ 31, 1, 2018 },
		{ 10, 2, 2018 },
		{ 10, 3, 2018 },
		{ 10, 4, 2018 },
		{ 20, 1, 2019 },
		{ 10, 1, 2019 }
	};

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE DATA: OPERADOR SUMA +="},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de l'operador de suma +=" << endl;
	outputParcial << "======================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data inicial: "; escriuData(dates[i], outputParcial); outputParcial << endl;
		outputParcial << "N. dies a sumar: " << nDies[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; escriuData(resultatEsperat[i], outputParcial); outputParcial << endl;
		Data resultat = dates[i];
		resultat += nDies[i];
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; escriuData(resultat, outputParcial); outputParcial << endl;
		if (igualDies(resultat, resultatEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.1;
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

	if (reduccio > 0.25)
		reduccio = 0.25;
	return reduccio;
}

float testIncrement(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 5;
	Data dates[N_PROVES] = 
	{
		{ 10, 1, 2018 },
		{ 28, 2, 2018 },
		{ 31, 1, 2018 },
		{ 31, 12, 2018 },
		{ 28, 2, 2020}
	};

	Data resultatEsperat[N_PROVES] =
	{
		{ 11, 1, 2018 },
		{ 1, 3, 2018 },
		{ 1, 2, 2018 },
		{ 1, 1, 2019 },
		{ 29, 2, 2020 }
	};

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE DATA: OPERADOR INCREMENT ++"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de l'operador increment ++" << endl;
	outputParcial << "========================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data inicial: "; escriuData(dates[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; escriuData(resultatEsperat[i], outputParcial); outputParcial << endl;
		Data resultat = dates[i];
		++resultat;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; escriuData(resultat, outputParcial); outputParcial << endl;
		if (igualDies(resultat, resultatEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.1;
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

	if (reduccio > 0.25)
		reduccio = 0.25;
	return reduccio;
}

float testRestaDates(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 8;
	Data dates1[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 20, 12, 2018 },
		{ 10, 1, 2018 }
	};

	Data dates2[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 11, 1, 2018 },
		{ 31, 1, 2018 },
		{ 10, 2, 2018 },
		{ 10, 3, 2018 },
		{ 10, 4, 2018 },
		{ 20, 1, 2019 },
		{ 10, 1, 2019 }
	};


	int nDiesEsperat[N_PROVES] = { 0, 1, 21, 31, 59, 90, 31, 365 };

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE DATA: OPERADOR RESTA DATES"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de l'operador resta de dates" << endl;
	outputParcial << "==========================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data 1: "; escriuData(dates1[i], outputParcial); outputParcial << endl;
		outputParcial << "Data 2: "; escriuData(dates2[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: " << nDiesEsperat[i] << endl;
		int resultat = dates1[i] - dates2[i];
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << resultat << endl;
		if (resultat == nDiesEsperat[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
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

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}

float testRestaDies(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 8;
	Data dates1[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 11, 1, 2018 },
		{ 31, 1, 2018 },
		{ 10, 2, 2018 },
		{ 10, 3, 2018 },
		{ 10, 4, 2018 },
		{ 20, 1, 2019 },
		{ 10, 1, 2019 }
	};

	Data datesEsperades[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 20, 12, 2018 },
		{ 10, 1, 2018 }
	};

	int nDies[N_PROVES] = { 0, 1, 21, 31, 59, 90, 31, 365 };

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE DATA: OPERADOR RESTA DIES"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de l'operador resta de dies" << endl;
	outputParcial << "=========================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data: "; escriuData(dates1[i], outputParcial); outputParcial << endl;
		outputParcial << "N. dies: " << nDies[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; escriuData(datesEsperades[i], outputParcial); outputParcial << endl;
		Data resultat = dates1[i] - nDies[i];
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; escriuData(resultat, outputParcial); outputParcial << endl;
		if (igualDies(datesEsperades[i], resultat))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
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

	if (reduccio > 1.0)
		reduccio = 1.0;
	return reduccio;
}


string dataToString(const Data& data)
{
	string resultat;
	resultat = to_string(data.getDia()) + "/" + to_string(data.getMes()) + "/" + to_string(data.getAny());
	return resultat;
}

void mostraArrayString(string arrayString[], int nElements, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < (nElements - 1); i++)
		outputParcial << arrayString[i] << ", ";
	if (nElements > 0)
		outputParcial << arrayString[nElements - 1];
	outputParcial << "]" << endl;
}

void afegeixTasques(GestioProjecte& gp, string& outputFinal)
{
	const int N_PROVES = 5;
	string nomTasca[N_PROVES] = { "T1", "T2", "T3", "T4", "T5"};
	Data dataInicial(15, 3, 2025);
	int nDies[N_PROVES] = {10, 30, 60, 20, 40};
	int nParticipants[N_PROVES] = {3, 2, 2, 3, 4};
	string participants[N_PROVES][MAX_PARTICIPANTS] = 
	{
		{ "P1", "P2", "P3" },
		{ "P2", "P4" },
		{ "P2", "P3" },
		{ "P1", "P3", "P4" },
		{ "P1", "P2", "P3", "P5" }
 	};
    stringstream outputParcial;

	outputParcial << "Afegim les tasques seguents amb el metode afegeixTasca" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "Nom: " << nomTasca[i] << endl;
		outputParcial << "Data actual: " << dataToString(dataInicial) << endl;
		outputParcial << "Dies previstos: " << nDies[i] << endl;
		outputParcial << "Participants: ";
		mostraArrayString(participants[i], nParticipants[i], outputParcial);
        gp.afegeixTasca(nomTasca[i], nDies[i], dataInicial, nParticipants[i], participants[i]);
		outputParcial << "----------" << endl;
        cout << outputParcial.str();
        outputFinal += outputParcial.str();
        outputParcial.str("");
	}
}


float testEndarrereixTasca(GestioProjecte& gp, json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST ENDARREREIX TASCA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test metode endarrereixTasca" << endl;
	outputParcial << "=====================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	string nomTasca = "T1";
	int nDies = 5;
	Data dataEsperada(30, 3, 2025);

	outputParcial << "Nom de la tasca: " << nomTasca << endl;
	outputParcial << "Dies a endarrerir: " << nDies << endl;
	outputParcial << "----------" << endl;
	outputParcial << "Nova data de finalitzacio prevista esperda: " << dataToString(dataEsperada) << endl;
	outputParcial << "----------" << endl;
	gp.endarrereixTasca(nomTasca, nDies);
	Data dataPrevista;
	bool completada;
	Data dataFinal;
	gp.recuperaTasca(nomTasca, dataPrevista, completada, dataFinal);
	outputParcial << "Data de finalitzacio prevista obtinguda: " << dataToString(dataPrevista) << endl;
	outputParcial << "----------" << endl;
	if (dataEsperada == dataPrevista)
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 0.5;
	}
	outputParcial << "-----------------------------------------------" << endl;
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


float testCompletaTasca(GestioProjecte& gp, json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST COMPLETA TASCA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test metode completaTasca" << endl;
	outputParcial << "==================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_PROVES = 2;
	string nomTasca[N_PROVES] = { "T2", "T3" };
	Data dataFinal[N_PROVES] = { {31, 3, 2025}, {15, 6, 2025} };
	int nDiesRetard[N_PROVES] = { 14, -32 };

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Nom de la tasca: " << nomTasca[i] << endl;
		outputParcial << "Data final: " << dataToString(dataFinal[i]) << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Dies de diferencia previstos: " << nDiesRetard[i] << endl;
		outputParcial << "----------" << endl;
		int nDies = gp.completaTasca(nomTasca[i], dataFinal[i]);
		outputParcial << "Dies de diferencia obtinguts: " << nDies << endl;
		outputParcial << "----------" << endl;
		if (nDies == nDiesRetard[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
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

	if (reduccio > 0.5)
		reduccio = 0.5;

	return reduccio;
}

bool pertanyElement(const string& element, string array[], int nElements)
{
	bool trobat = false;
	int i = 0;
	while ((i < nElements) && !trobat)
	{
		if (element == array[i])
			trobat = true;
		else
			i++;
	}
	return trobat;
}

bool igualArrayString(string array1[], int nElements1, string array2[], int nElements2)
{
	bool iguals = true;
	int i = 0;
	while ((i < nElements1) && iguals)
	{
		if (!pertanyElement(array1[i], array2, nElements2))
			iguals = false;
		else
			i++;
	}
	i = 0;
	while ((i < nElements2) && iguals)
	{
		if (!pertanyElement(array2[i], array1, nElements1))
			iguals = false;
		else
			i++;
	}
	return iguals;
}

float testTasquesPendents(GestioProjecte& gp, json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	ofstream jsonFile;

	const int N_PROVES = 3;
	string nomPersona = "P1";
	Data dataActual(15, 3, 2025);
	int nDies[N_PROVES] = {30, 60, 10};
	int nTasquesEsperades[N_PROVES] = {2, 3, 0};
	string tasquesEsperades[N_PROVES][MAX_TASQUES] = { {"T1", "T4"}, {"T1", "T4", "T5"}, {} };
	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
        stringstream outputParcial;

        outputTest =
        {
            {"name", "TEST TASQUES PENDENTS " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

		outputParcial << "TEST TASQUES PENDENTS " << i + 1 << endl;
		outputParcial << "Nom de la persona: " << nomPersona << endl;
		outputParcial << "Data actual: " << dataToString(dataActual) << endl;
		outputParcial << "N. dies: " << nDies[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "N. de tasques esperades: " << nTasquesEsperades[i] << endl;
		outputParcial << "Tasques esperades: ";
		mostraArrayString(tasquesEsperades[i], nTasquesEsperades[i], outputParcial);
		outputParcial << "----------" << endl;
		int nTasquesObtingudes = 0;
		string tasquesObtingudes[MAX_TASQUES];
		gp.tasquesPendents(nomPersona, dataActual, nDies[i], nTasquesObtingudes, tasquesObtingudes);
		outputParcial << "N. de tasques obtingudes: " << nTasquesObtingudes << endl;
		outputParcial << "Tasques obtingudes: ";
		mostraArrayString(tasquesObtingudes, nTasquesObtingudes, outputParcial);
		outputParcial << "----------" << endl;
		bool correcte = true;
		if (igualArrayString(tasquesEsperades[i], nTasquesEsperades[i], tasquesObtingudes, nTasquesObtingudes))
			outputParcial << "CORRECTE" << endl;
		else
		{
			correcte = false;
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "-----------------------------------------------" << endl;

        cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

        if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 0.5;
        }		    
	    else
		    outputTest["status"] = "failed";

        outputGeneral["score"] = grade;
        outputGeneral["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << outputGeneral << endl;
        jsonFile.close();
	}


	if (reduccio > 2.5)
		reduccio = 2.5;

	return reduccio;
}

float testRetardTasques(GestioProjecte& gp, json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	ofstream jsonFile;

	const int N_PROVES = 3;
	Data dataActual[N_PROVES] = {{20, 3, 2025}, {1, 4, 2025}, {15, 4, 2025}};
	int nPersonesEsperades[N_PROVES] = {0, 3, 4};
	string personesEsperades[N_PROVES][MAX_PARTICIPANTS] = { {}, {"P1", "P2", "P3"}, {"P1", "P2", "P3", "P4"} };
	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
        stringstream outputParcial;

        outputTest =
        {
            {"name", "TEST RETARD TASQUES " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

		outputParcial << "TEST RETARD TASQUES " << i + 1 << endl;
		outputParcial << "Data actual: " << dataToString(dataActual[i]) << endl;
		outputParcial << "----------" << endl;
		outputParcial << "N. de persones esperades: " << nPersonesEsperades[i] << endl;
		outputParcial << "Persones esperades: ";
		mostraArrayString(personesEsperades[i], nPersonesEsperades[i], outputParcial);
		outputParcial << "----------" << endl;
		int nPersonesObtingudes = 0;
		string personesObtingudes[MAX_PARTICIPANTS];
		gp.retardTasques(dataActual[i], nPersonesObtingudes, personesObtingudes);
		outputParcial << "N. de persones obtingudes: " << nPersonesObtingudes << endl;
		outputParcial << "Persones obtingudes: ";
		mostraArrayString(personesObtingudes, nPersonesObtingudes, outputParcial);
		outputParcial << "----------" << endl;
		bool correcte = true;
		if (igualArrayString(personesEsperades[i], nPersonesEsperades[i], personesObtingudes, nPersonesObtingudes))
			outputParcial << "CORRECTE" << endl;
		else
		{
			correcte = false;
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "-----------------------------------------------" << endl;

        cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

        if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 0.5;
        }		    
	    else
		    outputTest["status"] = "failed";

        outputGeneral["score"] = grade;
        outputGeneral["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << outputGeneral << endl;
        jsonFile.close();
	}


	if (reduccio > 2.5)
		reduccio = 2.5;

	return reduccio;
}

/*
AFEGEIX TASCA: { T1, 15/03/25, 10, { P1, P2, P3 } }
AFEGEIX TASCA: { T2, 15/03/25, 30, { P2, P4 } }
AFEGEIX TASCA: { T3, 15/03/25, 60, { P2, P3 } }
AFEGEIX TASCA: { T4, 15/03/25, 20, { P1, P3, P4 } }
AFEGEIX TASCA: { T5, 15/03/25, 40, { P1, P2, P3, P5 } }
ENDARREREIX TASCA: { T1, 5 } + RECUPERA
COMPLETA TASCA: { T2, 31/03/25 } + RECUPERA
COMPLETA TASCA: { T3, 15/06/25 } + RECUPERA
TASQUES PENDENTS: P1, 15/03/25, 30 -> {T1, T4]}
TASQUES PENDENTS: P1, 15/03/25, 60 -> {T1, T4, T5}
TASQUES PENDENTS: P1, 15/03/25, 10 -> {}
RETARD TASQUES: 20/03/25 -> 0, { }
RETARD TASQUES: 01/04/25 -> 3, {P1, P2, P3 }
RETARD TASQUES: 15/04/25 -> 4, {P1, P2, P3, P4 }

*/
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

	json outputTestOperadorsES;
	float reduccio = testOperadorsES(outputTestOperadorsES);
	grade = grade + (0.25 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestOperadorsES);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestComparaDates;
	reduccio = testComparaDates(outputTestComparaDates);
	grade = grade + (0.25 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestComparaDates);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestSumaDies;
	reduccio = testSumaDies(outputTestSumaDies);
	grade = grade + (1.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestSumaDies);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	
	json outputTestIgualSuma;
	reduccio = testIgualSuma(outputTestIgualSuma);
	grade = grade + (0.25 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestIgualSuma);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestIncrement;
	reduccio = testIncrement(outputTestIncrement);
	grade = grade + (0.25 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestIncrement);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestRestaDates;
	reduccio = testRestaDates(outputTestRestaDates);
	grade = grade + (1.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestRestaDates);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestRestaDies;
	reduccio = testRestaDies(outputTestRestaDies);
	grade = grade + (1.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestRestaDies);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	string outputGeneral;

	GestioProjecte gp;
    afegeixTasques(gp, outputGeneral);

    cout << outputGeneral << endl;
	output["output"] = outputGeneral;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestEndarrereixTasca;
	reduccio = testEndarrereixTasca(gp, outputTestEndarrereixTasca);
	grade = grade + (0.5 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestEndarrereixTasca);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestCompletaTasca;
	reduccio = testCompletaTasca(gp, outputTestCompletaTasca);
	grade = grade + (0.5 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestCompletaTasca);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	reduccio = testTasquesPendents(gp, output);
    grade = grade + (2.5 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	reduccio = testRetardTasques(gp, output);
    grade = grade + (2.5 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}



