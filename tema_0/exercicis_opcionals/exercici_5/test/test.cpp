#include "../source/joc.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraCarta(int carta[2], stringstream& outputParcial)
{
	outputParcial << "{";
	switch (carta[0])
	{
	case VERMELL: 
		outputParcial << "VERMELL";
		break;
	case VERD:
		outputParcial << "VERD";
		break;
	case BLAU:
		outputParcial << "BLAU";
		break;
	case GROC:
		outputParcial << "GROC";
		break;
	default:
		outputParcial << "---";
		break;
	}
	outputParcial << ", " << carta[1];
	outputParcial << "}";
}


void mostraMoviment(int moviment[4], stringstream& outputParcial)
{
	outputParcial << "Jug. " << moviment[0];
	switch (moviment[1])
	{
	case ROBA_CARTA:
		outputParcial << " ROBA CARTA ";
		break;
	case TIRA_CARTA:
		outputParcial << " TIRA CARTA ";
		break;
	case PASSA_TORN:
		outputParcial << " PASSA TORN ";
		break;
	}
	mostraCarta(&moviment[2], outputParcial);
}

void mostraCartesJugador(int cartes[MAX_CARTES][2], int jugador, stringstream& outputParcial)
{
	for (int i = jugador * 7; i < (jugador + 1) * 7; i++)
	{
		mostraCarta(cartes[i], outputParcial);
		outputParcial << ",";
	}
}

bool comparaMoviment(int movimentEsperat[4], int moviment[4])
{
	bool iguals = true;
	int i = 0;
	while (iguals && (i < 4))
	{
		if (movimentEsperat[i] != moviment[i])
			iguals = false;
		else
			i++;
	}
	return iguals;
}

float comparaMoviments(int movimentsEsperats[MAX_MOVIMENTS][4], int nMovimentsEsperat,
	int moviments[MAX_MOVIMENTS][4], int nMoviments, stringstream& outputParcial)
{
	bool iguals = true;
	float reduccio = 0.0;
	for (int i = 0; i < nMovimentsEsperat; i++)	
	{
		if (!comparaMoviment(movimentsEsperats[i], moviments[i]))
		{
			iguals = false;
			reduccio += 1.0;
		}
	}
	if (!iguals)
	{
		outputParcial << "ERROR. ELS MOVIMENTS NO SON IGUALS ALS ESPERATS" << endl;
	}
	if (nMovimentsEsperat != nMoviments)
	{
		outputParcial << "ERROR. EL NUMERO DE MOVIMENTS NO ES IGUAL AL NUMERO DE MOVIMENTS ESPERAT" << endl;
		reduccio += 4.0;
	}
	if (iguals && (nMovimentsEsperat == nMoviments))
	{
		outputParcial << "CORRECTE" << endl;
	}
	return reduccio;
}


float testMoviments(json& output)
{
	float grade = 10.0;

	int cartesInicials[MAX_CARTES][2] =
	{
		{VERMELL, 0}, {VERMELL, 3}, {VERMELL, 6}, {VERMELL, 9}, {VERD, 2}, {VERD, 5}, {VERD, 8},
		{VERMELL, 1}, {VERMELL, 4}, {VERMELL, 7}, {VERD, 0}, {VERD, 3}, {VERD, 6}, {VERD, 9},
		{VERMELL, 2}, {VERMELL, 5}, {VERMELL, 8}, {VERD, 1}, {VERD, 4}, {VERD, 7}, {BLAU, 0},
		{BLAU, 1}, {BLAU, 2}, {BLAU, 3}, {BLAU, 4}, {BLAU, 5}, {BLAU, 6}, {BLAU, 7},{BLAU, 8}, {BLAU, 9},
		{GROC, 0}, {GROC, 1}, {GROC, 2}, {GROC, 3}, {GROC, 4}, {GROC, 5}, {GROC, 6}, {GROC, 7},{GROC, 8}, {GROC, 9},
	};
	int movimentsEsperats[MAX_MOVIMENTS][4] =
	{
		{0, ROBA_CARTA, BLAU, 2}, {0, TIRA_CARTA, BLAU, 2}, {1, ROBA_CARTA, BLAU, 3}, {1, TIRA_CARTA, BLAU, 3},
		{2, TIRA_CARTA, BLAU, 0}, {0, TIRA_CARTA, VERMELL, 0}, {1, TIRA_CARTA, VERMELL, 7}, {2, TIRA_CARTA, VERMELL, 8}, 
		{0, TIRA_CARTA, VERMELL, 9}, {1, TIRA_CARTA, VERMELL, 4}, {2, TIRA_CARTA, VERMELL, 5}, {0, TIRA_CARTA, VERMELL, 6},
		{1, TIRA_CARTA, VERMELL, 1}, {2, TIRA_CARTA, VERMELL, 2}, {0, TIRA_CARTA, VERMELL, 3}, {1, TIRA_CARTA, VERD, 3},
		{2, TIRA_CARTA, VERD, 7}, {0, TIRA_CARTA, VERD, 8}, {1, TIRA_CARTA, VERD, 9}, {2, TIRA_CARTA, VERD, 4},
		{0, TIRA_CARTA, VERD, 5}, {1, TIRA_CARTA, VERD, 6}, {2, TIRA_CARTA, VERD, 1}
	};
	int nJugadors = 3;
	int nMovimentsEsperat = 23;

	int moviments[MAX_MOVIMENTS][4];
	int nMoviments;

	stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST PARTIDA"},
        {"visibility", "visible"},
        {"output", ""}
    };
	
	outputParcial << endl;
	outputParcial << "Execucio de la partida completa" << endl;
	outputParcial << "===============================" << endl;
	outputParcial << "" << endl;
	outputParcial << "......." << endl;

	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");	

	jugaPartida(cartesInicials, nJugadors, moviments, nMoviments);


	outputParcial << endl;
	outputParcial << "------------------------------------------" << endl;
	outputParcial << "Final de la partida" << endl;

	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");	

	outputParcial << endl;
	outputParcial << "Comprovacio dels moviments que s'han fet a la partida" << endl;
	outputParcial << "=====================================================" << endl;

	outputParcial << "Cartes inicials esperades pel jugador 0: " << endl;
	mostraCartesJugador(cartesInicials, 0, outputParcial);
	outputParcial << endl;
	outputParcial << "Cartes inicials esperades pel jugador 1: " << endl;
	mostraCartesJugador(cartesInicials, 1, outputParcial);
	outputParcial << endl;
	outputParcial << "Cartes inicials esperades pel jugador 2: " << endl;
	mostraCartesJugador(cartesInicials, 2, outputParcial);
	outputParcial << endl;
	outputParcial << "Carta inicial del joc: ";
	mostraCarta(cartesInicials[nJugadors * 7], outputParcial);
	outputParcial << endl;

	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");	

	outputParcial << "----------------------------" << endl;
	outputParcial << "Comparacio de moviments esperats i obtinguts:" << endl;
	for (int i = 0; i < nMovimentsEsperat; i++)
	{
		outputParcial << "Esperat: ";
		mostraMoviment(movimentsEsperats[i], outputParcial);
		outputParcial << endl;
		outputParcial << "Obtingut: ";
		mostraMoviment(moviments[i], outputParcial);
		outputParcial << endl;
		outputParcial << "---------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");	
	}
	
	float reduccio = comparaMoviments(movimentsEsperats, nMovimentsEsperat, moviments, nMoviments, outputParcial);

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


int main()
{	
	float grade = 0.0;
	cout << "Grade :=>> " << grade << endl;

	json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "hidden";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestMoviments;
	float reduccio = testMoviments(outputTestMoviments);
	grade += (10 - reduccio);
	if (grade < 0)
		grade = 0.0;
	output["score"] = grade;
	output["tests"].push_back(outputTestMoviments);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	cout << "------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}