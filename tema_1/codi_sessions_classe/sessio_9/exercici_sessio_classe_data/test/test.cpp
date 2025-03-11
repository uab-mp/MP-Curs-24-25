#include "../source/data.h"
#include "../source/operacions_data.h"
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
		{"name", "TEST OPERADORS E/S"},
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
		reduccio += 0.5;
	}
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio > 1.0)
		reduccio = 1.0;
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
		{"name", "TEST OPERADORS COMPARACIO"},
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
		{"name", "TEST OPERADOR SUMA"},
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

	if (reduccio > 2.0)
		reduccio = 2.0;
	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 4.0)
		reduccio = 4.0;
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
		{"name", "TEST OPERADOR SUMA +="},
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
		{"name", "TEST OPERADOR INCREMENT ++"},
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

	ifstream fitxerTest;
	fitxerTest.open("dates_input.txt");
	streambuf* buffer_cin = cin.rdbuf(fitxerTest.rdbuf());


	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST COMPROVA TERMINI"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio comprovaTermini" << endl;
	outputParcial << "==========================================" << endl;
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
		bool resultat = comprovaTermini();
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		if (resultat == resultatEsperat[i])
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
		{"name", "TEST OPERADOR RESTA DATES"},
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

	if (reduccio > 2.0)
		reduccio = 2.0;
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
		{"name", "TEST OPERADOR RESTA DIES"},
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

	json outputTestOperadorsES;
	float reduccio = testOperadorsES(outputTestOperadorsES);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestOperadorsES);
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
	
	json outputTestIgualSuma;
	reduccio = testIgualSuma(outputTestIgualSuma);
	grade = grade + (1.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestIgualSuma);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestIncrement;
	reduccio = testIncrement(outputTestIncrement);
	grade = grade + (1.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestIncrement);
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

	json outputTestRestaDies;
	reduccio = testRestaDies(outputTestRestaDies);
	grade = grade + (1.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestRestaDies);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestTerminiValid;
	reduccio = testTerminiValid(outputTestTerminiValid);
	grade = grade + (1.0 - reduccio);
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



#include <iostream>

