#include "../source/venda_entrades.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using json = nlohmann::json;

const int N_SEIENTS = 20;

void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "T";
	else
		outputParcial << "F";
}

void mostraResultat(EstatCompra resultat, stringstream& outputParcial, char operacio)
{
    switch(resultat)
    {
    case COMPRA_OK:
        if (operacio == 'C')
            outputParcial << "COMPRA CORRECTA";
        else
            outputParcial << "ANUL.LACIO CORRECTA";
        break;
    case ERROR_ESPECTACLE:
        outputParcial << "ESPECTACLE NO EXISTEIX";
        break;
    case ERROR_SEIENTS: 
        if (operacio == 'C')
            outputParcial << "NO HI HA SEIENTS DISPONIBLES";
        else
            outputParcial << "HI HA SEIENTS NO RESERVATS";
        break;
    }
}

void mostraSeients(int seients[], int nSeients, stringstream& outputParcial)
{
    for (int i = 0; i < (nSeients - 1); i++)
        outputParcial << seients[i] << ",";
    outputParcial << seients[nSeients - 1];
}

void mostraOcupacio(bool ocupacio[], stringstream& outputParcial)
{
    for (int i = 0; i < (N_SEIENTS - 1); i++)
    {
        mostraBool(ocupacio[i], outputParcial);
        outputParcial << ",";
    }
    mostraBool(ocupacio[N_SEIENTS - 1], outputParcial);
}

bool comparaSeients(int seients[], int seientsEsperats[], int nSeients)
{
    bool iguals = true;
    int i = 0;
    while (iguals && (i < nSeients))
    {
        if (seients[i] != seientsEsperats[i])
            iguals = false;
        else
            i++;
    }
    return iguals;
}

bool comparaOcupacio(bool ocupacio[], bool ocupacioEsperada[])
{
    bool iguals = true;
    int i = 0;
    while (iguals && (i < N_SEIENTS))
    {
        if (ocupacio[i] != ocupacioEsperada[i])
            iguals = false;
        else
            i++;
    }
    return iguals;
}

void afegeixEspectacles(VendaEntrades& gestioEntrades, string& outputFinal)
{
	float reduccio = 0;
	const int N_PROVES = 5;
	string nomEspectacle[N_PROVES] = { "E1", "E2", "E3", "E4", "E5"};
	string data[N_PROVES] = { "01/01/2025" , "01/02/2025", "01/03/2025", "01/04/2025", "01/05/2025"};
	float preu[N_PROVES] = { 50.0, 40.0, 30.0, 50.0, 40.0};
    stringstream outputParcial;

	outputParcial << "Afegim els espectacles seguents amb el metode afegeixEspectacle" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "Nom: " << nomEspectacle[i] << endl;
		outputParcial << "Data: " << data[i] << endl;
		outputParcial << "Preu: " << preu[i] << endl;
        gestioEntrades.afegeixEspectacle(nomEspectacle[i], data[i], preu[i]);
		outputParcial << "----------" << endl;
        cout << outputParcial.str();
        outputFinal += outputParcial.str();
        outputParcial.str("");
	}
}

float testVendaEntrades(VendaEntrades& gestioEntrades, json& output)
{
	float reduccio = 0;

	const int N_PROVES = 14;
    char operacio[N_PROVES] = { 'C', 'C', 'C', 'C', 'C', 'C', 'A', 'A', 'C', 'C', 'C', 'A', 'A', 'A' };
	string espectacle[N_PROVES] = { "E3", "E6", "E2", "E2", "E2", "E2", "E2", "E2", "E2", "E2", "E2", "E2", "E2", "E2" };
	string data[N_PROVES] = { "01/01/2024" , "01/01/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/02/2025", "01/01/2024" };
	int nEntrades[N_PROVES] = { 10, 10, 4, 8, 6, 4, 4, 4, 6, 4, 1, 2, 2, 2 };
	EstatCompra resultatEsperat[N_PROVES] = { ERROR_ESPECTACLE, ERROR_ESPECTACLE, COMPRA_OK, COMPRA_OK, COMPRA_OK, ERROR_SEIENTS, COMPRA_OK, COMPRA_OK, COMPRA_OK, COMPRA_OK, ERROR_SEIENTS, COMPRA_OK, ERROR_SEIENTS, ERROR_ESPECTACLE };
    int seientsEsperats[N_PROVES][MAX_SEIENTS_COMPRA] = 
    {
        {},
        {},
        {1, 2, 3, 4},
        {5, 6, 7, 8 ,9, 10, 11, 12},
        {13, 14, 15, 16, 17, 18},
        {},
        {6, 8, 10, 12},
        {1, 2, 3, 4},
        {1, 2, 3, 4, 6, 8},
        {10, 12, 19, 20},
        {},
        {1, 2},
        {1, 3},
        {1, 3}
    };
	int preuEsperat[N_PROVES] = { -1, -1, 160, 304, 228, -1, -1, -1, 204, 144, -1, -1, -1, -1 };
    bool ocupacioEsperada[MAX_SEIENTS];
    for (int i = 0; i < MAX_SEIENTS; i++)
        ocupacioEsperada[i] = false;

    stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST VENDA ENTRADES"},
		{"visibility", "visible"},
		{"output", ""}
	};


	outputParcial << "Iniciant test del metode compraEntrades" << endl;
	outputParcial << "=======================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
        bool correcte = true;
		outputParcial << "TEST " << i + 1 << ": ";
        if (operacio[i] == 'C')
            outputParcial << "Compra d'entrades " << endl;
        else
            outputParcial << "Anul.lacio d'entrades " << endl;
        outputParcial << "-----------------------" << endl;
        outputParcial << "Nom: " << espectacle[i] << endl;
		outputParcial << "Data: " << data[i] << endl;
		outputParcial << "N. entrades: " << nEntrades[i] << endl;
        if (operacio[i] == 'A')
        {
            outputParcial << "Seients anul·lats: ";
            mostraSeients(seientsEsperats[i], nEntrades[i], outputParcial);
            outputParcial << endl;
        }
        outputParcial << "------" << endl;
        outputParcial << "Resultat Esperat: ";
        mostraResultat(resultatEsperat[i], outputParcial, operacio[i]);
        outputParcial << endl;
        if (operacio[i] == 'C')
        {
            float preu;
            int seients[MAX_SEIENTS_COMPRA];
            if (resultatEsperat[i] == COMPRA_OK)
            {
                outputParcial << "Preu esperat: " << preuEsperat[i] << endl;
                outputParcial << "Seients assignats esperats: ";
                mostraSeients(seientsEsperats[i], nEntrades[i], outputParcial);
                outputParcial << endl;
                for (int j = 0; j < nEntrades[i]; j++)
                    ocupacioEsperada[seientsEsperats[i][j] - 1] = true;
                outputParcial << "Ocupacio dels seients esperada: ";
                mostraOcupacio(ocupacioEsperada, outputParcial);
                outputParcial << endl;
    
            }
            outputParcial << "------" << endl;
            EstatCompra resultat = gestioEntrades.compraEntrades(espectacle[i], data[i], nEntrades[i], preu, seients);
            outputParcial << "Resultat Obtingut: ";
            mostraResultat(resultat, outputParcial, operacio[i]);
            outputParcial << endl;
            correcte = (resultat == resultatEsperat[i]);   
            if (resultat == COMPRA_OK)
            {
                outputParcial << "Preu obtingut: " << preu << endl;
                outputParcial << "Seients assignats obtinguts: ";
                mostraSeients(seients, nEntrades[i], outputParcial);
                outputParcial << endl;
                bool ocupacio[MAX_SEIENTS];
                gestioEntrades.recuperaOcupacio(espectacle[i], data[i], ocupacio);
                outputParcial << "Ocupacio dels seients obtinguda: ";
                mostraOcupacio(ocupacio, outputParcial);
                outputParcial << endl;

                correcte = correcte && (preu == preuEsperat[i]) && 
                                    comparaSeients(seients, seientsEsperats[i], nEntrades[i])
                                    && comparaOcupacio(ocupacio, ocupacioEsperada);
            }
        }
        else
        {
            if (resultatEsperat[i] == COMPRA_OK)
            {
                for (int j = 0; j < nEntrades[i]; j++)
                    ocupacioEsperada[seientsEsperats[i][j] - 1] = false;
                outputParcial << "Ocupacio dels seients esperada: ";
                mostraOcupacio(ocupacioEsperada, outputParcial);
                outputParcial << endl;
    
            }
            outputParcial << "------" << endl;
            EstatCompra resultat = gestioEntrades.anulaCompra(espectacle[i], data[i], nEntrades[i], seientsEsperats[i]);
            outputParcial << "Resultat Obtingut: ";
            mostraResultat(resultat, outputParcial, operacio[i]);
            outputParcial << endl;
            correcte = (resultat == resultatEsperat[i]);   
            if (resultat == COMPRA_OK)
            {
                bool ocupacio[MAX_SEIENTS];
                outputParcial << "Ocupacio dels seients obtinguda: ";
                gestioEntrades.recuperaOcupacio(espectacle[i], data[i], ocupacio);
                mostraOcupacio(ocupacio, outputParcial);
                outputParcial << endl;

                correcte = correcte && comparaOcupacio(ocupacio, ocupacioEsperada);
            }
            
        }
        outputParcial << "------" << endl;
        if (correcte)
            outputParcial << "CORRECTE" << endl;
        else
        {
            outputParcial << "ERROR" << endl;
            reduccio += 1.0;
        }
		outputParcial << "-----------------------------------------------------------------------" << endl;
        cout << outputParcial.str();
        outputFinal += outputParcial.str();
        outputParcial.str("");
	}

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
    json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "hidden";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

    stringstream outputParcial;
	string outputGeneral;

    outputParcial << "Inicialitzem la Venda d'Entrades amb el constructor amb " << N_SEIENTS << " seients" << endl;
	outputParcial << "-------------------------------------------------" << endl;
	cout << outputParcial.str();
	outputGeneral += outputParcial.str();
	outputParcial.str("");

	VendaEntrades gestioEntrades(N_SEIENTS);
    afegeixEspectacles(gestioEntrades, outputGeneral);

    cout << outputParcial.str();
	outputGeneral += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputGeneral;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

    json outputTestCompraEntrades;
	float reduccio = testVendaEntrades(gestioEntrades, outputTestCompraEntrades);
	grade = grade + (10 - reduccio);
    if (grade < 0)
    grade = 0.0;
	output["score"] = grade;
	output["tests"].push_back(outputTestCompraEntrades);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();


	cout << "Grade :=>> " << grade << endl;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	return 0;
}