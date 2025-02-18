#include "../source/batalla_naval.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraTauler(EstatTauler taulerResultat[N_FILES][N_COLUMNES], stringstream& output)
{
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            switch (taulerResultat[i][j])
            {
            case ESTAT_NUL:
                output << "-";
                break;
            case ESTAT_AIGUA:
                output << "X";
                break;
            case ESTAT_TOCAT:
                output << "T";
                break;
            case ESTAT_ENFONSAT:
                output << "E";
                break;
            case ESTAT_VAIXELL:
                output << "V";
                break;            }
        }
        output << endl;
    }
}

bool comparaTauler(EstatTauler taulerResultat[N_FILES][N_COLUMNES], EstatTauler taulerFinal[N_FILES][N_COLUMNES])
{
    bool iguals = true;
    int i = 0;
    while ((i < N_FILES) && iguals)
    {
        int j = 0;
        while ((j < N_COLUMNES) && iguals)
        {
            if (taulerResultat[i][j] != taulerFinal[i][j])
                iguals = false;
            j++;
        }
        i++;
   }
    return iguals;
}

float testPartidaAcabada(json& output)
{
    float reduccio = 0.0;
    stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST PARTIDA ACABADA"},
        {"visibility", "visible"},
        {"output", ""}
    };

    EstatTauler taulerInicial[N_FILES][N_COLUMNES] = 
    {
        {ESTAT_VAIXELL, ESTAT_VAIXELL, ESTAT_VAIXELL, ESTAT_VAIXELL, ESTAT_AIGUA},
        {ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA},
        {ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_VAIXELL},
        {ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_VAIXELL},
        {ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_VAIXELL}
    };

    EstatTauler taulerFinal[N_FILES][N_COLUMNES] = 
    {
        {ESTAT_ENFONSAT, ESTAT_ENFONSAT, ESTAT_ENFONSAT, ESTAT_ENFONSAT, ESTAT_AIGUA},
        {ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA},
        {ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_ENFONSAT, ESTAT_AIGUA, ESTAT_ENFONSAT},
        {ESTAT_ENFONSAT, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_ENFONSAT},
        {ESTAT_ENFONSAT, ESTAT_AIGUA, ESTAT_ENFONSAT, ESTAT_AIGUA, ESTAT_ENFONSAT}
    };

	outputParcial << "Test de la funcio Batalla Naval. Partida acabada" << endl;
	outputParcial << "================================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

    outputParcial << endl;
    outputParcial << "TAULER INCIAL PER ENDEVINAR: " << endl;
    outputParcial << "-----------------------------" << endl;
    mostraTauler(taulerInicial, outputParcial);
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");


    stringstream inputStream;
    inputStream.str("2 1 1 2 2 2 1 3 1 4 1 5 1 1 3 5 3 4 4 5 5 5 3 3 4 1 5 1 5 3");
    streambuf *bufferOriginalIn = cin.rdbuf(inputStream.rdbuf());

    stringstream outputStream;
    streambuf *bufferOriginalOut = cout.rdbuf(outputStream.rdbuf());


    int nIntents = 20;
    EstatTauler taulerResultat[N_FILES][N_COLUMNES];
    bool acabada = batallaNaval(taulerInicial, nIntents, taulerResultat);

    cin.rdbuf(bufferOriginalIn);
    cout.rdbuf(bufferOriginalOut);

    const int N_INTENTS = 15;
    int posicions[N_INTENTS][2] = {{2, 1}, {1, 2}, {2, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 1}, {3, 5}, {3, 4}, {4, 5}, {5, 5}, {3, 3}, {4, 1}, {5, 1}, {5, 3}};
    string resultat[N_INTENTS] = {"AIGUA", "TOCAT", "AIGUA", "TOCAT", "TOCAT", "AIGUA", "ENFONSAT", "TOCAT", "AIGUA", "TOCAT", "ENFONSAT", "ENFONSAT", "TOCAT", "ENFONSAT", "ENFONSAT"}; 

    outputParcial << endl;
    outputParcial << "SEQUENCIA DE JUGADES" << endl;
    outputParcial << "--------------------" << endl;
    for (int i = 0; i < N_INTENTS; i++)
    {
        outputParcial << "Intent " << i + 1 << endl;
        outputParcial << "----------" << endl;
        outputParcial << "Posicio: (" << posicions[i][0] << ", " << posicions[i][1] << ")" << endl;
        outputParcial << "Resultat: " << resultat[i] << endl;
        outputParcial << "----------" << endl;
    }
    cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

    outputParcial << endl;
    outputParcial << "SORTIDA PER PANTALLA DE LA FUNCIO BATALLA NAVAL: " << endl;
    outputParcial << "--------------------------------------------------" << endl;
    cout << outputParcial.str();
	outputFinal += outputParcial.str();
    outputParcial.str("");

    cout << outputStream.str();
    outputFinal += outputStream.str();

    outputParcial << endl;
    outputParcial << "TAULER FINAL ESPERAT: " << endl;
    outputParcial << "--------------------" << endl;
    mostraTauler(taulerFinal, outputParcial);
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");

    outputParcial << endl;
    outputParcial << "TAULER FINAL OBTINGUT: " << endl;
    outputParcial << "---------------------" << endl;
    mostraTauler(taulerResultat, outputParcial);
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");

    outputParcial << endl;
    outputParcial << "--------------------" << endl;
    bool correcte = comparaTauler(taulerFinal, taulerResultat);
    if (correcte)
        outputParcial << "TAULER RESULTAT CORRECTE" << endl;
    else
    {
        outputParcial << "TAULER RESULTAT INCORRECTE" << endl;
        reduccio += 4.0;
    }
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");

    outputParcial << endl;
    outputParcial << "--------------------" << endl;
    if (acabada)
        outputParcial << "PARTIDA ACABADA. RESULTAT CORRECTE" << endl;
    else
    {
        outputParcial << "PARTIDA NO ACABADA. RESULTAT INCORRECTE" << endl;
        reduccio += 2.0;
    }
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

float testPartidaNoAcabada(json& output)
{
    float reduccio = 0.0;
    stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST PARTIDA NO ACABADA"},
        {"visibility", "visible"},
        {"output", ""}
    };

    EstatTauler taulerInicial[N_FILES][N_COLUMNES] = 
    {
        {ESTAT_VAIXELL, ESTAT_VAIXELL, ESTAT_VAIXELL, ESTAT_VAIXELL, ESTAT_AIGUA},
        {ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA},
        {ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_VAIXELL},
        {ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_VAIXELL},
        {ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_VAIXELL, ESTAT_AIGUA, ESTAT_VAIXELL}
    };

    EstatTauler taulerFinal[N_FILES][N_COLUMNES] = 
    {
        {ESTAT_ENFONSAT, ESTAT_ENFONSAT, ESTAT_ENFONSAT, ESTAT_ENFONSAT, ESTAT_AIGUA},
        {ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA, ESTAT_AIGUA},
        {ESTAT_NUL, ESTAT_NUL, ESTAT_NUL, ESTAT_AIGUA, ESTAT_TOCAT},
        {ESTAT_NUL, ESTAT_NUL, ESTAT_NUL, ESTAT_NUL, ESTAT_TOCAT},
        {ESTAT_NUL, ESTAT_NUL, ESTAT_NUL, ESTAT_NUL, ESTAT_NUL}
    };

	outputParcial << "Test de la funcio Batalla Naval. Partida acabada" << endl;
	outputParcial << "================================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

    outputParcial << endl;
    outputParcial << "TAULER INCIAL PER ENDEVINAR: " << endl;
    outputParcial << "-----------------------------" << endl;
    mostraTauler(taulerInicial, outputParcial);
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");


    stringstream inputStream;
    inputStream.str("2 1 1 2 2 2 1 3 1 4 1 5 1 1 3 5 3 4 4 5");
    streambuf *bufferOriginalIn = cin.rdbuf(inputStream.rdbuf());

    stringstream outputStream;
    streambuf *bufferOriginalOut = cout.rdbuf(outputStream.rdbuf());


    int nIntents = 10;
    EstatTauler taulerResultat[N_FILES][N_COLUMNES];
    bool acabada = batallaNaval(taulerInicial, nIntents, taulerResultat);

    cin.rdbuf(bufferOriginalIn);
    cout.rdbuf(bufferOriginalOut);

    const int N_INTENTS = 10;
    int posicions[N_INTENTS][2] = {{2, 1}, {1, 2}, {2, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 1}, {3, 5}, {3, 4}, {4, 5}};
    string resultat[N_INTENTS] = {"AIGUA", "TOCAT", "AIGUA", "TOCAT", "TOCAT", "AIGUA", "ENFONSAT", "TOCAT", "AIGUA", "TOCAT"}; 

    outputParcial << endl;
    outputParcial << "SEQUENCIA DE JUGADES" << endl;
    outputParcial << "--------------------" << endl;
    for (int i = 0; i < N_INTENTS; i++)
    {
        outputParcial << "Intent " << i + 1 << endl;
        outputParcial << "----------" << endl;
        outputParcial << "Posicio: (" << posicions[i][0] << ", " << posicions[i][1] << ")" << endl;
        outputParcial << "Resultat: " << resultat[i] << endl;
        outputParcial << "----------" << endl;
    }
    cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

    outputParcial << endl;
    outputParcial << "SORTIDA PER PANTALLA DE LA FUNCIO BATALLA NAVAL: " << endl;
    outputParcial << "--------------------------------------------------" << endl;
    cout << outputParcial.str();
	outputFinal += outputParcial.str();
    outputParcial.str("");

    cout << outputStream.str();
    outputFinal += outputStream.str();

    outputParcial << endl;
    outputParcial << "TAULER FINAL ESPERAT: " << endl;
    outputParcial << "--------------------" << endl;
    mostraTauler(taulerFinal, outputParcial);
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");

    outputParcial << endl;
    outputParcial << "TAULER FINAL OBTINGUT: " << endl;
    outputParcial << "---------------------" << endl;
    mostraTauler(taulerResultat, outputParcial);
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");

    outputParcial << endl;
    outputParcial << "--------------------" << endl;
    bool correcte = comparaTauler(taulerFinal, taulerResultat);
    if (correcte)
        outputParcial << "TAULER RESULTAT CORRECTE" << endl;
    else
    {
        outputParcial << "TAULER RESULTAT INCORRECTE" << endl;
        reduccio += 4.0;
    }
    cout << outputParcial.str();
    outputFinal += outputParcial.str();
    outputParcial.str("");

    outputParcial << endl;
    outputParcial << "--------------------" << endl;
    if (acabada)
    {
        outputParcial << "PARTIDA ACABADA. RESULTAT INCORRECTE" << endl;
        reduccio += 2.0;
    }
    else
        outputParcial << "PARTIDA NO ACABADA. RESULTAT CORRECTE" << endl;
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
	json output;
	ofstream jsonFile;
	float grade = 0.0;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "hidden";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

    json outputTestPartidaAcabada;
	float reduccio = testPartidaAcabada(outputTestPartidaAcabada);
	grade = grade + (5 - reduccio);
	cout << endl << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestPartidaAcabada);

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

    json outputTestPartidaNoAcabada;
	reduccio = testPartidaNoAcabada(outputTestPartidaNoAcabada);
	grade = grade + (5 - reduccio);
    if (grade < 0)
        grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestPartidaNoAcabada);

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

    if (grade < 0)
        grade = 0.0;
    if (grade == 10.0)
        cout << "Final del test sense errors" << endl;

	return 0;
}
