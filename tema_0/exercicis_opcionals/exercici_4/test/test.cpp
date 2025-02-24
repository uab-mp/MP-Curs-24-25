
#include "../source/data.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraVector(int v[], int longitud, stringstream& outputParcial)
{
	outputParcial << "[";
	if (longitud > 0)
	{
		outputParcial << v[0];
	}
	for (int i = 1; i < longitud; i++)
		outputParcial << "," << v[i];
	outputParcial << "]";
}

bool igualVectors(int v1[], int v2[], int longitud)
{
	bool iguals = true;
	int i = 0;
	while ((iguals) && (i < longitud))
	{
		if (v1[i] != v2[i])
			iguals = false;
		i++;
	}
	return iguals;
}

void escriuData(Data& diaG, stringstream& outputParcial)
{
	outputParcial << diaG.dia << "/" << diaG.mes << "/" << diaG.any;
}

bool igualDies(Data& dia1, Data& dia2)
{
	return ((dia1.dia == dia2.dia) && (dia1.mes == dia2.mes) && (dia1.any == dia2.any));
}

void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "TRUE ";
	else
		outputParcial << "FALSE ";
}

float testLlegeixDia(json& output)
{
	float reduccio = 0.0;

	Data resultat;
	streambuf* orig = std::cin.rdbuf();
	istringstream input("13\n9\n2014");
	Data resultatEsperat;
	resultatEsperat.dia = 13;
	resultatEsperat.mes = 9;
	resultatEsperat.any = 2014;

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST LLEGEIX DIA"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio llegeixDia" << endl;
	outputParcial << "=====================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");	

	outputParcial << "Llegint valors de l'entrada" << endl;
	outputParcial << "----------" << endl;
	outputParcial << "Resultat esperat: "; escriuData(resultatEsperat, outputParcial); outputParcial << endl;
	cin.rdbuf(input.rdbuf());
	llegeixDia(resultat);
	cin.rdbuf(orig);
	outputParcial << "----------" << endl;
	outputParcial << "Resultat obtingut: "; escriuData(resultat, outputParcial); outputParcial << endl;
	if (igualDies(resultat, resultatEsperat))
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 2.0;
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


float testEsValida(json &output)
{
	float reduccio = 0.0;

	const int N_PROVES = 8;
	Data dates[N_PROVES] = { { 29, 2, 1996 },{ 29, 2, 1900 },{ 0, 1, 2000 },{ 31, 12, 1997 },{ 1, 1, 2004 },{ 31, 4, 1997 },{ 30,4,2003 },{ 0,3,1703 } };
	bool valid[N_PROVES] = { true, false, false, true, true, false, true,false };

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST ES VALIDA"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio esValida" << endl;
	outputParcial << "===================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");	
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data: "; escriuData(dates[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; mostraBool(valid[i], outputParcial); outputParcial << endl;
		bool resultat = esValida(dates[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		if (resultat == valid[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
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

	if (reduccio > 4.0)
		reduccio = 4.0;
	return reduccio;
}


float testComparaDates(json &output)	
{
	float reduccio = 0.0;

	const int N_PROVES = 9;
	Data dates1[N_PROVES] = { { 1, 1, 1996 },{ 1, 1, 1900 },{ 2, 1, 1900 },{ 1, 1, 2000 },{ 31, 12, 1999 },{ 1, 1, 1997 },{ 1, 2, 1997 },{ 1, 1, 2006 },{ 1, 1, 2004 } };
	Data dates2[N_PROVES] = { { 1, 1, 1996 },{ 2, 1, 1900 },{ 1, 1, 1900 },{ 31, 12, 1999 },{ 1, 1, 2000 },{ 1, 2, 1997 },{ 1, 1, 1997 },{ 1, 1, 2004 }, { 1, 1, 2006 } };
	int iguals[N_PROVES] = { 0, -1, 1, 1, -1, -1, 1, 1, -1};

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST COMPARA DATES"},
        {"visibility", "visible"},
        {"output", ""}
    };
	
	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio comparaDates" << endl;
	outputParcial << "=======================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");	
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data 1: "; escriuData(dates1[i], outputParcial); outputParcial << endl;
		outputParcial << "Data 2: "; escriuData(dates2[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: " << iguals[i] << endl;
		int resultat = comparaDates(dates1[i], dates2[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << resultat << endl;
		if (resultat == iguals[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
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

	if (reduccio > 3.0)
		reduccio = 3.0;
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
        {"name", "TEST SUMA DIES"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio sumaDies" << endl;
	outputParcial << "===================================" << endl;
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
		Data resultat = sumaDies(dates[i], nDies[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; escriuData(resultat, outputParcial); outputParcial << endl;
		if (igualDies(resultat, resultatEsperat[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
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

	if (reduccio > 4.0)
		reduccio = 4.0;
	return reduccio;
}


float testTerminiValid(json& output)
{
	float reduccio = 0.0;

	const int N_PROVES = 5;
	Data dates[N_PROVES] =
	{
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 },
		{ 10, 1, 2018 }
	};
	int nDiesTermini[N_PROVES] = { 90, 90, 365, 365, 365 };
	Data dataActual[N_PROVES] =
	{
		{ 10, 4, 2018 },
		{ 11, 4, 2018 },
		{ 31, 12, 2018 },
		{ 10, 2, 2019 },
		{ 10, 1, 2020}
	};
	bool resultatEsperat[N_PROVES] = { true, false, true, false, false };

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST TERMINI VALID"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio terminiValid" << endl;
	outputParcial << "=======================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");	
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Data inicial: "; escriuData(dates[i], outputParcial); outputParcial << endl;
		outputParcial << "N. dies termini: " << nDiesTermini[i] << endl;
		outputParcial << "Data actual: "; escriuData(dataActual[i], outputParcial); outputParcial << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
		bool resultat = terminiValid(dates[i], nDiesTermini[i], dataActual[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		if (resultat == resultatEsperat[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
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

	if (reduccio > 4.0)
		reduccio = 4.0;
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
        {"name", "TEST LLEGEIX DIA"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio restaDates" << endl;
	outputParcial << "=====================================" << endl;
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
		int resultat = restaDates(dates1[i], dates2[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << resultat << endl;
		if (resultat == nDiesEsperat[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
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

	if (reduccio > 4.0)
		reduccio = 4.0;
	return reduccio;
}

int main()
{
	float grade = 0.0;

	json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "hidden";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestLlegeixDia;
	float reduccio = testLlegeixDia(outputTestLlegeixDia);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestLlegeixDia);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestEsValida;
	reduccio = testEsValida(outputTestEsValida);
	grade = grade + (2.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestEsValida);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	
	json outputTestComparaDates;
	reduccio = testComparaDates(outputTestComparaDates);
	grade = grade + (1.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestComparaDates);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestSumaDies;
	reduccio = testSumaDies(outputTestSumaDies);
	grade = grade + (2.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestSumaDies);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestRestaDates;
	reduccio = testRestaDates(outputTestRestaDates);
	grade = grade + (2.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestRestaDates);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestTerminiValid;
	reduccio = testTerminiValid(outputTestTerminiValid);
	grade = grade + (2.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestTerminiValid);
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