#include "../source/tauler.h"
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


int main()
{
	float reduccio = 0;
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

	Tauler t;

	const int N_CASELLES = 12;
	int estatCaselles[N_CASELLES][2] =
	{
		{1, 1},
		{2, 1},
		{3, 2},
		{4, 1},
		{5, 2},
		{6, 1},
		{7, 3},
		{8, 1},
		{9, 4},
		{10, 2},
		{11, 1},
		{12, 5}
	};
	


	json outputTestInicialitza;
	stringstream outputParcial;
	string outputFinal = "";

	outputTestInicialitza =
	{
		{"name", "TEST INICIALITZACIO PARTIDA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	cout << endl << "Grade :=>> " << grade << endl << endl;
	outputParcial << endl;
	outputParcial << "Inicialitzant tauler de joc amb 3 jugadors" << endl;
	outputParcial << "==========================================" << endl;
	outputParcial << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	int tipusCaselles[N_CASELLES];
	for (int i = 0; i < N_CASELLES; i++)
		tipusCaselles[i] = estatCaselles[i][1];
	t.inicialitza(tipusCaselles, N_CASELLES, 3);
	outputParcial << "Comprovant estat caselles despres inicialitzar" << endl;
	outputParcial << "----------------------------------------------" << endl; 
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_CASELLES; i++)
	{
		outputParcial << "CASELLA " << i + 1 << endl;
		outputParcial << "Tipus esperat: " << estatCaselles[i][1] << endl;
		outputParcial << "---" << endl;
		outputParcial << "Tipus obtingut: " << t.getTipusCasella(i + 1) << endl;
		if (estatCaselles[i][1] == t.getTipusCasella(i + 1))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "---" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	outputTestInicialitza["output"] = outputFinal;

	if (reduccio == 0)
		outputTestInicialitza["status"] = "passed";
	else
		outputTestInicialitza["status"] = "failed";
	if (reduccio > 2.0)
		reduccio = 2.0;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	output["score"] = grade;
	output["tests"].push_back(outputTestInicialitza);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();


	outputFinal = "";
	const int N_TORNS = 14;
	const int N_JUGADORS = 3;
	int valorDau[N_TORNS] = { 2, 2, 5, 4, 3, 2, 3, 1, 2, 1, 2, 1, 2, 1 };
	int posicioJugadors[N_TORNS][N_JUGADORS] = 
	{
		{5, 1, 1},
		{7, 1, 1},
		{7, 6, 1},
		{7, 6, 10},
		{7, 6, 10},
		{7, 6, 10},
		{7, 1, 10},
		{7, 1, 11},
		{7, 1, 11},
		{7, 2, 11},
		{7, 2, 11},
		{8, 2, 11},
		{8, 4, 11},
		{8, 4, 12}
	};
	bool potTirarJugadors[N_TORNS][N_JUGADORS] =
	{
		{true, true, true},
		{false, true, true},
		{false, true, true},
		{false, true, true},
		{false, true, true},
		{false, true, true},
		{false, true, true},
		{false, true, true},
		{true, true, true},
		{true, true, true},
		{true, true, true},
		{true, true, true},
		{true, true, true},
		{true, true, true}
	};
	int nTornsInactiuJugadors[N_TORNS][N_JUGADORS] =
	{
		{0, 0, 0},
		{2, 0, 0},
		{2, 0, 0},
		{2, 0, 0},
		{2, 0, 0},
		{1, 0, 0},
		{1, 0, 0},
		{1, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};
	bool guanyadorJugadors[N_TORNS][N_JUGADORS] =
	{
		{false, false, false},
		{false, false, false},
		{false, false, false},		
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, false},
		{false, false, true}
	};

	json outputTestPartida;

	outputTestPartida =
	{
		{"name", "TEST FUNCIONAMENT PARTIDA"},
		{"visibility", "visible"},
		{"output", ""}
	};
	outputParcial << "" << endl;
	outputParcial << "Comprovant el funcionament del joc amb el metode tornJoc de la classe Tauler" << endl;
	outputParcial << "============================================================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	for (int i = 0; i < N_TORNS; i++)
	{
		outputParcial << "TORN " << i + 1 << endl;
		outputParcial << "Valor del dau: " << valorDau[i] << endl;
		t.tornJoc(valorDau[i]);
		outputParcial << "---" << endl;
		outputParcial << "Estat esperat dels jugadors: " << endl;
		for (int j = 0; j < N_JUGADORS; j++)
		{
			outputParcial << "Jugador " << j << ": Posicio = " << posicioJugadors[i][j] <<
				", Pot Tirar = "; mostraBool(potTirarJugadors[i][j], outputParcial);
			outputParcial << ", N. torns sense tirar: " << nTornsInactiuJugadors[i][j] << ", Guanyador: "; mostraBool(guanyadorJugadors[i][j], outputParcial); outputParcial << endl;
		}
		outputParcial << "---" << endl;
		outputParcial << "Estat obtingut dels jugadors: " << endl;
		int posicio, nTornsInactiu;
		bool potTirar, guanyador;
		for (int j = 0; j < N_JUGADORS; j++)
		{
			t.getEstatJugador(j + 1, posicio, potTirar, nTornsInactiu, guanyador);
			outputParcial << "Jugador " << j << ": Posicio = " << posicio <<
				", Pot Tirar = "; mostraBool(potTirar, outputParcial);
			outputParcial << ", N. torns sense tirar: " << nTornsInactiu << ", Guanyador: "; mostraBool(guanyador, outputParcial); outputParcial << endl;
			if ((posicio == posicioJugadors[i][j]) && (potTirar == potTirarJugadors[i][j]) && 
				(nTornsInactiu == nTornsInactiuJugadors[i][j]) && (guanyador == guanyadorJugadors[i][j]))
				outputParcial << "CORRECTE" << endl;
			else
			{
				outputParcial << "ERROR" << endl;
				reduccio += 1.0;
			}

		}		
		outputParcial << "------------------------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	outputTestPartida["output"] = outputFinal;

	if (reduccio == 0)
		outputTestPartida["status"] = "passed";
	else
		outputTestPartida["status"] = "failed";

	if (reduccio > 8.0)
		reduccio = 8.0;
	grade += (8.0 - reduccio);
	output["score"] = grade;
	output["tests"].push_back(outputTestPartida);
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