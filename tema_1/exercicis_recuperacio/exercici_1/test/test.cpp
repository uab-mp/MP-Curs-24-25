#include "../source/activitat.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

const int MAX_USUARIS = 5;
const int MAX_ACTIVITATS = 3;

void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "TRUE ";
	else
		outputParcial << "FALSE ";
}

float testClasseUsuari(json& output)
{
	float reduccio = 0.0;
	
	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE USUARI"},
		{"visibility", "visible"},
		{"output", ""}
	};

	string nomSoci[MAX_USUARIS] = { "Usuari_1", "Usuari_2", "Usuari_3", "Usuari_4", "Usuari_5"};
	string codiSoci[MAX_USUARIS] = { "Codi_1", "Codi_2", "Codi_3", "Codi_4", "Codi_5"};
	int edatSoci[MAX_USUARIS] = { 18, 60, 40, 35, 40 };

	outputParcial <<  endl;
	outputParcial << "Iniciant test del constructor de la classe Usuari" << endl;
	outputParcial << "=================================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < MAX_USUARIS; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Creant un nou usuari ... " << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat despres inicialitzacio: " << endl;
		outputParcial << "Codi: " << codiSoci[i] << endl;
		outputParcial << "Nom: " << nomSoci[i] << endl;
		outputParcial << "Edat: " << edatSoci[i] << endl;
		Usuari u(codiSoci[i], nomSoci[i], edatSoci[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut despres inicialitzacio: " << endl;
		outputParcial << "Codi: " << u.getCodi() << endl;
		outputParcial << "Nom: " << u.getNom() << endl;
		outputParcial << "Edat: " << u.getEdat() << endl;
		if ((u.getCodi()!=codiSoci[i])||(u.getNom()!=nomSoci[i])||(u.getEdat()!= edatSoci[i]))
		{
			outputParcial << "ERROR " << endl;
			reduccio += 2.0;
		}
		else
		{
			outputParcial << "CORRECTE" << endl;
		}
		outputParcial << "-----------------------------" << endl;
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

float testClasseActivitat(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE ACTIVITAT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	string nomActivitats[MAX_ACTIVITATS] = { "Activitat_1", "Activitat_2", "Activitat_3" };
	string dies[MAX_ACTIVITATS] = { "dilluns", "dimarts", "dimecres" };
	string hores[MAX_ACTIVITATS] = { "9:00", "8:00", "18:00" };
	int edatMinima[MAX_ACTIVITATS] = { 18, 30, 40 };
	int edatMaxima[MAX_ACTIVITATS] = { 60, 70, 100 };
	int maximParticipants[MAX_ACTIVITATS] = { 3, 3, 15 };

	outputParcial <<  endl;
	outputParcial << "Iniciant test del constructor de la classe Activitat" << endl;
	outputParcial << "====================================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < MAX_ACTIVITATS; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Creant una nova activitat... " << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat despres inicialitzacio: " << endl;
		outputParcial << "Nom: " << nomActivitats[i] << endl;
		outputParcial << "Dia: " << dies[i] << endl;
		outputParcial << "Hora: " << hores[i] << endl;
		outputParcial << "Edat Minima: " << edatMinima[i] << endl;
		outputParcial << "Edat Maxima: " << edatMaxima[i] << endl;
		outputParcial << "Maxim participants: " << maximParticipants[i] << endl;
		outputParcial << "N. participants: " << 0 << endl;
		Activitat a(nomActivitats[i], maximParticipants[i], edatMinima[i], edatMaxima[i], dies[i], hores[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut despres inicialitzacio: " << endl;
		outputParcial << "Nom: " << a.getNom() << endl;
		outputParcial << "Dia: " << a.getDia() << endl;
		outputParcial << "Hora: " << a.getHora() << endl;
		outputParcial << "Edat Minima: " << a.getEdatMinima() << endl;
		outputParcial << "Edat Maxima: " << a.getEdatMaxima() << endl;
		outputParcial << "Maxim participants: " << a.getMaximParticipants() << endl;
		outputParcial << "N. participants: " << a.getParticipants() << endl;
		if ((a.getNom() != nomActivitats[i]) || (a.getDia() != dies[i]) || (a.getHora() != hores[i]) || (a.getEdatMinima() != edatMinima[i]) ||
			(a.getEdatMaxima() != edatMaxima[i]) || (a.getMaximParticipants() != maximParticipants[i]) || (a.getParticipants() != 0))
		{
			outputParcial << "ERROR " << endl;
			reduccio += 2.0;
		}
		else
		{
			outputParcial << "CORRECTE" << endl;
		}
		outputParcial << "-----------------------------" << endl;
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

	
float testAfegeixBuscaParticipant(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CLASSE ACTIVITAT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial <<  endl;
	outputParcial << "Iniciant test del metode afegeixParticipant" << endl;
	outputParcial << "===========================================" << endl;
	outputParcial << "-----------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	string nomAct = "activitat_1";
	int maximParticipantsAct = 3;
	int edatMinimaAct = 30;
	int edatMaximaAct = 50;
	string diaAct = "dilluns";
	string horaAct = "10:00";
	Activitat a(nomAct, maximParticipantsAct, edatMinimaAct, edatMaximaAct, diaAct, horaAct);
	outputParcial << "Inicialitzant activitat...." << endl;
	outputParcial << "Nom: " << nomAct << endl;
	outputParcial << "Dia: " << diaAct << endl;
	outputParcial << "Hora: " << horaAct << endl;
	outputParcial << "Edat Minima: " << edatMinimaAct << endl;
	outputParcial << "Edat Maxima: " << edatMaximaAct << endl;
	outputParcial << "Maxim participants: " << maximParticipantsAct << endl;
	outputParcial << "-----------------------------" << endl;
	outputParcial << "-----------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_PROVES = 7;
	Usuari usuaris[N_PROVES] = 
	{
		{"codi_1", "nom_1", 18}, 
		{"codi_1", "nom_1", 60}, 
		{"codi_1", "nom_1", 40}, 
		{"codi_1", "nom_1", 35}, 
		{"codi_2", "nom_2", 40},
		{"codi_3", "nom_3", 40}, 
		{"codi_4", "nom_4", 40}
	};
	int resultatEsperat[N_PROVES] = { -1, -1, 0, -2, 0, 0, -3 };
	int nParticipants[N_PROVES] = { 0, 0, 1, 1, 2, 3, 3 };

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Afegint usuari ... " << endl;
		outputParcial << "Codi: " << usuaris[i].getCodi() << endl;
		outputParcial << "Nom: " << usuaris[i].getNom() << endl;
		outputParcial << "Edat: " << usuaris[i].getEdat() << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: " << resultatEsperat[i] << endl;
		outputParcial << "N. participants esperat: " << nParticipants[i] << endl;
		int resultat = a.afegeixParticipant(usuaris[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: " << resultat << endl;
		outputParcial << "N. participants despres afegir: " << a.getParticipants() << endl;
		if (resultat == resultatEsperat[i])
		{
			if (resultat == 0)
				if (a.getParticipants() == nParticipants[i])
					outputParcial << "CORRECTE" << endl;
				else
				{
					outputParcial << "ERROR " << endl;
					reduccio += 2.0;
				}
			else
				outputParcial << "CORRECTE" << endl;
		}
		else
		{
			outputParcial << "ERROR " << endl;
			reduccio += 2.0;
		}
		outputParcial << "----------------------------" << endl;
		outputParcial << "-----------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	outputParcial <<  endl;
	outputParcial << "Iniciant test del metode buscarParticipant" << endl;
	outputParcial << "(suposem que s'han afegit els participants del test anterior correctament)" << endl;
	outputParcial << "==========================================================================" << endl;
	outputParcial << "-----------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	const int N_PROVES_BUSCAR = 5;
	bool resultatEsperatBuscar[N_PROVES_BUSCAR] = { true, true, true, false, false };
	string noms[N_PROVES_BUSCAR] = { "nom_1", "nom_2", "nom_3", "nom_4", "nom_5" };
	for (int i = 0; i < N_PROVES_BUSCAR; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "Buscant participant amb nom: " << noms[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: ";  mostraBool(resultatEsperatBuscar[i], outputParcial); outputParcial << endl;
		bool resultat = a.buscaParticipant(noms[i]);
		outputParcial << "----------" << endl;
		outputParcial << "Resultat obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
		if (resultat == resultatEsperatBuscar[i])
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR " << endl;
			reduccio += 2.0;
		}
		outputParcial << "----------------------------" << endl;
		outputParcial << "-----------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	
	if (reduccio > 8.0)
		reduccio = 8.0;

	return reduccio;
}

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

	json outputTestClasseUsuari;
	float reduccio = testClasseUsuari(outputTestClasseUsuari);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestClasseUsuari);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestClasseActivitat;
	reduccio = testClasseActivitat(outputTestClasseActivitat);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestClasseActivitat);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestAfegeixBuscaParticipant;
	reduccio = testAfegeixBuscaParticipant(outputTestAfegeixBuscaParticipant);
	grade = grade + (8 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestAfegeixBuscaParticipant);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}