#include "../source/quatre_ratlla.h"
#include <string>
#include "json.hpp"
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

void mostraMatriu(int v[N_FILES][N_COLUMNES], stringstream& outputParcial)
{
	for (int i = 0; i < N_FILES; i++)
	{
		outputParcial << "";
		for (int j = 0; j < N_COLUMNES; j++)
			outputParcial << v[i][j] << " ";
		outputParcial << endl;
	}
}


bool comparaMatrius(int v1[N_FILES][N_COLUMNES], int v2[N_FILES][N_COLUMNES])
{
	bool iguals = true;
	int i = 0;
	int j;
	while ((i < N_FILES) && iguals)
	{
		j = 0;
		while ((j < N_COLUMNES) && iguals)
		{
			if (v1[i][j] != v2[i][j])
				iguals = false;
			else j++;
		}
		i++;
	}
	return iguals;
}


float testPosaFitxa(json& output)
{
	const int N_PROVES = 5;
	int taulerInicial[N_PROVES][N_FILES][N_COLUMNES] =
	{
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 1 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 2, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 0 }
		}
	};
	int columna[N_PROVES] = { 2, 0, 1, 6, 3 };
	int jugador[N_PROVES] = { 1, 2, 1, 2, 2 };
	int taulerFinal[N_PROVES][N_FILES][N_COLUMNES] =
	{
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0, 0, 0 }
		},
		{
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 2 },
			{ 0, 0, 0, 0, 0, 0, 1 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 2, 0, 0, 0 },
			{ 0, 0, 0, 2, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 0 }
		}
	};
	int resultat[N_PROVES] = {5, -1, 0, 4, 3};

	float reduccio = 0.0;
	int resultatObtingut;

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST POSA FITXA"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio posaFitxa" << endl;
	outputParcial << "====================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Tauler inicial: " << endl; mostraMatriu(taulerInicial[i], outputParcial);
		resultatObtingut = posaFitxa(taulerInicial[i], columna[i], jugador[i]);
		outputParcial << "-----" << endl;
		outputParcial << "Tauler final esperat: " << endl; mostraMatriu(taulerFinal[i], outputParcial);
		outputParcial << "Resultat final esperat: " << resultat[i] << endl;
		outputParcial << "-----" << endl;
		outputParcial << "Tauler final obtingut: " << endl; mostraMatriu(taulerInicial[i], outputParcial);
		outputParcial << "Resultat final obtingut: " << resultatObtingut << endl;
		if ((resultatObtingut == resultat[i]) && comparaMatrius(taulerInicial[i], taulerFinal[i]))
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

	if (reduccio > 4.0)
		reduccio = 4.0;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	return reduccio;
}

float testQuatreRatlla(json& output)
{
	const int N_PROVES = 12;
	int taulerInicial[N_PROVES][N_FILES][N_COLUMNES] =
	{
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 2, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 2, 2, 2, 2, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 2, 2, 2, 2, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 2, 1, 0, 0, 0, 0, 0 },
			{ 2, 1, 0, 0, 0, 0, 0 },
			{ 2, 1, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 1, 0 },
			{ 0, 2, 1, 0, 1, 1, 0 },
			{ 0, 2, 2, 1, 2, 2, 0 },
			{ 0, 1, 1, 1, 2, 2, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 1, 0 },
			{ 0, 2, 1, 0, 1, 1, 0 },
			{ 0, 2, 2, 1, 2, 2, 0 },
			{ 0, 1, 1, 1, 2, 2, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 0, 0, 0, 0 },
			{ 0, 2, 1, 2, 1, 1, 0 },
			{ 0, 2, 2, 1, 2, 2, 0 },
			{ 0, 1, 1, 1, 2, 2, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 0, 0, 0, 0 },
			{ 0, 2, 1, 2, 1, 1, 0 },
			{ 0, 2, 2, 1, 2, 2, 0 },
			{ 0, 1, 1, 1, 2, 2, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 1, 0, 0, 1 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 2, 0, 0, 0 },
			{ 0, 2, 2, 2, 1, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 2, 0, 2, 0, 0, 0 },
			{ 0, 2, 2, 2, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 2, 0, 0, 0 },
			{ 0, 2, 0, 2, 1, 1, 1 }
		}
	};
	int fila[N_PROVES] = { 2, 5, 5, 5, 5, 4, 2, 4, 3, 4, 5, 5 };
	int columna[N_PROVES] = { 1, 1, 2, 1, 2, 3, 2, 4, 1, 1, 1, 1 };
	bool resultat[N_PROVES] = { true, true, true, true, true, true, true, true, false, false, false, false};

	float reduccio = 0.0;
	bool resultatObtingut;

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST POSA QUATRE RATLLA"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio quatreRatlla" << endl;
	outputParcial << "========================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Tauler: " << endl; mostraMatriu(taulerInicial[i], outputParcial);
		outputParcial << "Posicio a comprovar. Fila: " << fila[i] << ", Columna: " << columna[i] << endl;
		resultatObtingut = quatreRatlla(taulerInicial[i], fila[i], columna[i]);
		outputParcial << "-----" << endl;
		outputParcial << "Resultat esperat: "; mostraBool(resultat[i], outputParcial); outputParcial << endl;
		outputParcial << "-----" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultatObtingut, outputParcial); outputParcial << endl;

		if (resultatObtingut == resultat[i])
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
	}

	output["output"] = outputFinal;

	if (reduccio > 6.0)
		reduccio = 4.0;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	return reduccio;
}


float testJugaQuatreRatlla(json& output)
{
	const int N_PROVES = 2;
	int taulerInicial[N_PROVES][N_FILES][N_COLUMNES] =
	{
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 }
		}
	};
	int taulerFinal[N_PROVES][N_FILES][N_COLUMNES] =
	{
		{
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 2, 0, 1, 0, 0 },
			{ 1, 1, 1, 2, 1, 0, 0 },
			{ 2, 2, 1, 1, 2, 0, 0 },
			{ 1, 1, 1, 2, 2, 2, 0 },
			{ 1, 2, 2, 1, 2, 2, 0 }
		},
		{
			{ 2, 1, 2, 1, 2, 1, 2 },
			{ 1, 1, 2, 1, 2, 1, 2 },
			{ 2, 1, 2, 1, 2, 1, 2 },
			{ 1, 2, 1, 2, 1, 2, 1 },
			{ 2, 2, 1, 2, 1, 2, 1 },
			{ 1, 2, 1, 2, 1, 2, 1 }
		}
	};
	int resultat[N_PROVES] = { 2, -1 };

	ifstream fitxerTest;
	string nomFitxer;
	float reduccio = 0.0;
	int resultatObtingut;

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST JUGA QUATRE RATLLA"},
        {"visibility", "visible"},
        {"output", ""}
    };

	outputParcial << endl << endl;
	outputParcial << "Iniciant test de la funcio jugaQuatreRatlla" << endl;
	outputParcial << "===========================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << endl;
		outputParcial << "-----------------------------------------------" << endl;
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "-----------------------------------------------" << endl;
		outputParcial << "Tauler inicial: " << endl; mostraMatriu(taulerInicial[i], outputParcial);
		outputParcial << "-----" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");

		nomFitxer = "prova" + to_string(i + 1) + ".txt";
		int columna;
		int jugador = 1;
		fitxerTest.open(nomFitxer);
		fitxerTest >> columna;
		while (!fitxerTest.eof())
		{
			outputParcial << "Torn del jugador: " << jugador << " Columna: " << columna << endl;
			cout << outputParcial.str();
			outputFinal += outputParcial.str();
			outputParcial.str("");
			jugador = 3 - jugador;
			fitxerTest >> columna;
		}
		fitxerTest.close();

		fitxerTest.open(nomFitxer);
		streambuf* buffer_cin = cin.rdbuf(fitxerTest.rdbuf());

		resultatObtingut = jugaQuatreRatlla(taulerInicial[i]);

		cin.rdbuf(buffer_cin);
		fitxerTest.close();


		outputParcial << "-----" << endl;
		outputParcial << "Tauler final esperat: " << endl; mostraMatriu(taulerFinal[i], outputParcial);
		outputParcial << "Resultat final esperat: " << resultat[i] << endl;
		outputParcial << "-----" << endl;
		outputParcial << "Tauler final obtingut: " << endl; mostraMatriu(taulerInicial[i], outputParcial);
		outputParcial << "Resultat final obtingut: " << resultatObtingut << endl;
		if ((resultatObtingut == resultat[i]) && comparaMatrius(taulerInicial[i], taulerFinal[i]))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 4.0;
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	output["output"] = outputFinal;

	if (reduccio > 6.0)
		reduccio = 4.0;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

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

	json outputTestPosaFitxa;
	float reduccio = testPosaFitxa(outputTestPosaFitxa);
	grade = grade + (2.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestPosaFitxa);

	json outputTestQuatreRatlla;
	reduccio = testQuatreRatlla(outputTestQuatreRatlla);
	grade = grade + (4.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestQuatreRatlla);

	json outputTestJugaQuatreRatlla;
	reduccio = testJugaQuatreRatlla(outputTestJugaQuatreRatlla);
	grade = grade + (4.0 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestJugaQuatreRatlla);

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