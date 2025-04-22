#include "../source/tauler.hpp"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

const int N_FILES_TAULER = 8;
const int N_COLUMNES_TAULER = 8;

const int MAX_POSICIONS_POSSIBLES = 10;

void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "TRUE ";
	else
		outputParcial << "FALSE ";
}

void mostraArray(Posicio array[], int nElements, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < (nElements - 1); i++)
		outputParcial << array[i] << ", ";
	if (nElements > 0)
		outputParcial << array[nElements - 1];
	outputParcial << "]" << endl;
}

bool pertanyElement(const Posicio& element, Posicio array[], int nElements)
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

bool igualArrays(Posicio array1[], int nElements1, Posicio array2[], int nElements2)
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



void mostraTauler(char tauler[N_FILES_TAULER][N_COLUMNES_TAULER], stringstream& outputParcial)
{
    for (int fila = 0; fila < N_FILES_TAULER; fila++)
    {
        outputParcial << to_string(N_FILES_TAULER - fila) + ": ";
        for (int col = 0; col < N_COLUMNES_TAULER; col++){
            outputParcial << tauler[fila][col];
            if (col != N_COLUMNES_TAULER -1)
            {
                outputParcial <<  " ";
            }
        }
        outputParcial << endl;
    }
    
    outputParcial << "   a b c d e f g h" << endl;
}

bool comprovaTauler(char taulerEsperat[N_FILES_TAULER][N_COLUMNES_TAULER], string taulerObtingut)
{
    bool iguals = true;
    int fila = 0;
    int indexString = 0;
    int longitudString = taulerObtingut.length();
    while (iguals && (fila < N_FILES_TAULER) && (indexString < longitudString))    
    {
        int columna = 0;
        while (iguals && (columna < N_COLUMNES_TAULER) && (indexString < longitudString))
        {
            if ((taulerObtingut[indexString] == 'O') || (taulerObtingut[indexString] == 'X') || (taulerObtingut[indexString] == '_') || (taulerObtingut[indexString] == 'D') || (taulerObtingut[indexString] == 'R'))
                if (taulerObtingut[indexString] != taulerEsperat[fila][columna])
                    iguals = false;
                else
                {
                    indexString++;
                    columna++;
                }
            else
                indexString++; 
        }
        fila++;
    }
    return iguals;
}


void llegeixTauler(const string& nomFitxer, char estatTauler[N_FILES_TAULER][N_COLUMNES_TAULER])
{

    for (int i = 0; i < N_FILES_TAULER; i++)
    {
        for (int j = 0; j < N_COLUMNES_TAULER; j++)
        {
            estatTauler[i][j] = '_';
        }
    }
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        string pos;
        char fitxa;
        while (!fitxer.eof())
        {
            fitxer >> fitxa;
            fitxer >> pos;
            char columna = pos[0] - 'a';
            char fila = N_FILES_TAULER - (pos[1] - '0');
            estatTauler[fila][columna] = fitxa;
        }
        fitxer.close();
    }
}

float testTauler(int nTest, const string& nomFitxer, char taulerEsperat[N_FILES_TAULER][N_COLUMNES_TAULER], json& outputGeneral)
{
    float reduccio = 0.0;
    float grade = 0.0;

    ofstream jsonFile;
    json outputTest;
    stringstream outputParcial;

    outputTest =
    {
        {"name", "TEST INICIALITZA TAULER " + to_string(nTest)},
        {"visibility", "visible"},
        {"output", ""}
    };

    outputParcial << endl << endl;
    outputParcial << "TEST INICIALITZA TAULER " << nTest << endl;
    outputParcial << "===========================" << endl;
    outputParcial << endl;
    outputParcial << "Llegint estat del tauler del fitxer '" << nomFitxer << "'" << endl;
    outputParcial << "---------------" << endl;

    Tauler tauler;
    tauler.inicialitza(nomFitxer);

    outputParcial << "Contingut esperat del tauler: " << endl;
    mostraTauler(taulerEsperat, outputParcial);
    outputParcial << "---------------" << endl;
    outputParcial << "Contingut obtingut del tauler: " << endl;
    string taulerObtingut = tauler.toString();
    outputParcial << taulerObtingut << endl; 
    outputParcial << "---------------" << endl;

    bool correcte = comprovaTauler(taulerEsperat, taulerObtingut);
    if (correcte)
    {
        outputParcial << "CORRECTE" << endl;
        outputTest["status"] = "passed";
        grade += 0.5;
    }
    else
    {
        outputParcial << "ERROR" << endl;
        reduccio += 1.0;
        outputTest["status"] = "failed";
    }

    outputParcial << "-----------------------------------------------" << endl;
    
    cout << outputParcial.str();
    outputTest["output"] = outputParcial.str();
    outputParcial.str("");

    outputGeneral["score"] = grade;
    outputGeneral["tests"].push_back(outputTest);
    jsonFile.open("results.json");
    jsonFile << setw(4) << outputGeneral << endl;
    jsonFile.close();

    if (reduccio > 1.0)
        reduccio = 1.0;

    return reduccio;
}

float testLlegeixTauler(json& outputGeneral)
{
	float reduccio = 0.0;

    char taulerEsperat1[N_FILES_TAULER][N_COLUMNES_TAULER] = 
    {
        {'_', 'X', '_', 'X', '_', 'X', '_', 'X'},
        {'X', '_', 'X', '_', 'X', '_', 'X', '_'},
        {'_', 'X', '_', 'X', '_', 'X', '_', 'X'},
        {'_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_'},
        {'O', '_', 'O', '_', 'O', '_', 'O', '_'},
        {'_', 'O', '_', 'O', '_', 'O', '_', 'O'},
        {'O', '_', 'O', '_', 'O', '_', 'O', '_'}
    };

    char taulerEsperat2[N_FILES_TAULER][N_COLUMNES_TAULER] = 
    {
        {'_', 'X', '_', 'D', '_', '_', '_', 'X'},
        {'_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', 'X', '_', 'X', '_', '_'},
        {'R', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', 'X', '_', '_', '_', 'O'},
        {'X', '_', 'D', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', 'X'},
        {'O', '_', 'O', '_', 'D', '_', '_', '_'}
    };

    reduccio += testTauler(1, "tauler_inicial_1.txt", taulerEsperat1, outputGeneral);
    reduccio += testTauler(2, "tauler_inicial_2.txt", taulerEsperat2, outputGeneral);


    return reduccio;
}


float testMovimentsValids(json& outputGeneral)
{
    float reduccio = 0.0;
    float grade = outputGeneral["score"];

    ofstream jsonFile;
    char taulerEsperat[N_FILES_TAULER][N_COLUMNES_TAULER] = 
    {
        {'_', 'X', '_', '_', '_', '_', '_', 'X'},
        {'X', '_', 'X', '_', '_', '_', '_', '_'},
        {'_', 'O', '_', 'X', '_', 'X', '_', 'O'},
        {'R', '_', '_', '_', '_', '_', '_', '_'},
        {'_', 'O', '_', 'X', '_', 'X', '_', 'O'},
        {'_', '_', 'D', '_', 'O', '_', '_', '_'},
        {'_', 'O', '_', '_', '_', '_', '_', 'X'},
        {'O', '_', 'O', '_', 'D', '_', '_', '_'}
    };
    const int N_PROVES = 12;
    string posicions[N_PROVES] = { "b8", "a1", "c1", "h2", "d4", "b6", "f4", "a7", "e3", "a5", "e1", "c3" };
    Posicio posicionsPosssiblesEperades[N_PROVES][MAX_POSICIONS_POSSIBLES] = 
    {
        {},
        {},
        {Posicio("d2")},
        {Posicio("g1")},
        {Posicio("f2")},
        {Posicio("d8")},
        {Posicio("d2"), Posicio("g3")},
        {Posicio("c5"), Posicio("a3")},
        {Posicio("c5"), Posicio("g5"), Posicio("e7")},
        {},
        {Posicio("d2"), Posicio("f2"), Posicio("g3")},
        {Posicio("d2"), Posicio("e5"), Posicio("g3"), Posicio("g7")}
    };
    int nPosicionsEsperades[N_PROVES] = { 0, 0, 1, 1, 1, 1, 2, 2, 3, 0, 3, 4 };
    string nomFitxer = "tauler_moviments_valids.txt";
    for (int i = 0; i < N_PROVES;  i++)
    {
		json outputTest;
        stringstream outputParcial;

        outputTest =
        {
            {"name", "TEST MOVIMENTS VALIDS " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

        outputParcial << endl;
        outputParcial << "TEST MOVIMENTS VALIDS " << i + 1 << endl;
        outputParcial << "========================" << endl;
        outputParcial << endl;
        outputParcial << "Llegint estat del tauler del fitxer '" << nomFitxer << "'" << endl;
        outputParcial << "---------------" << endl;
    
        Tauler tauler;
        tauler.inicialitza(nomFitxer);
    
        outputParcial << "Contingut esperat del tauler: " << endl;
        mostraTauler(taulerEsperat, outputParcial);
        outputParcial << "---------------" << endl;
        outputParcial << "Contingut obtingut del tauler: " << endl;
        tauler.actualitzaMovimentsValids();
        string taulerObtingut = tauler.toString();
        outputParcial << taulerObtingut << endl; 
        outputParcial << "---------------" << endl;
        outputParcial << "Recuperant posicions possibles de la posicio: " << posicions[i] << endl;
        outputParcial << "----------" << endl;
        outputParcial << "Posicions possibles esperades: ";
        mostraArray(posicionsPosssiblesEperades[i], nPosicionsEsperades[i], outputParcial);
        outputParcial << "----------" << endl;
        int nPosicionsPossibles;
        Posicio posicionsPosssibles[MAX_POSICIONS_POSSIBLES];
        tauler.getPosicionsPossibles(Posicio(posicions[i]), nPosicionsPossibles, posicionsPosssibles);
        outputParcial << "Posicions possibles obitngudes: ";
        mostraArray(posicionsPosssibles, nPosicionsPossibles, outputParcial);
        outputParcial << "----------" << endl;
        bool correcte = igualArrays(posicionsPosssiblesEperades[i], nPosicionsEsperades[i], posicionsPosssibles, nPosicionsPossibles);
        if (correcte)
        {
            outputParcial << "CORRECTE" << endl;
            outputTest["status"] = "passed";
            grade += 0.5;
        }
        else
        {
            outputParcial << "ERROR" << endl;
            reduccio += 1.0;
            outputTest["status"] = "failed";
        }
    
        outputParcial << "-----------------------------------------------" << endl;
        
        cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");
    
        outputGeneral["score"] = grade;
        outputGeneral["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << outputGeneral << endl;
        jsonFile.close();
    }
    if (reduccio > 6.0)
        reduccio = 6.0;
    return reduccio;
}

float testMovimentFitxa(json& outputGeneral)
{
    float reduccio = 0.0;
    float grade = outputGeneral["score"];

    ofstream jsonFile;
    string nomFitxerInicial = "tauler_moviment_fitxa_";
    string nomFitxerFinal = "tauler_moviment_fitxa_resultat_";
    const int N_PROVES = 10;
    string posicioInicial[N_PROVES] = { "b8", "c3", "d4", "d4", "h8", "d4", "g7", "a3", "b4", "h8" };
    string posicioFinal[N_PROVES] = { "c7", "d4", "f6", "h8", "d4", "g7", "d4", "b4", "d6", "a5" };
    bool resultatEsperat[N_PROVES] = { false, true, true, true, true, true, true, true, true, true };
    string comentariMoviment[N_PROVES] = 
    { 
        "Moviment no valid",
        "Moviment fitxa normal sense matar",
        "Moviment fitxa normal amb captura",
        "Moviment fitxa normal amb doble captura i conversio a dama",
        "Moviment dama sense matar",
        "Moviment dama amb captura",
        "Moviment amb varies opcions de captura que no impliquen bufar fitxa",
        "Moviment sense matar que implica bufar la fitxa que podria matar",
        "Moviment que no mata totes les fitxer que es podrien matar i implica bufar la fitxa",
        "Moviment dama amb captura multiple"
    };




    for (int i = 0; i < N_PROVES;  i++)
    {
		json outputTest;
        stringstream outputParcial;

        outputTest =
        {
            {"name", "TEST MOVIMENT FITXA " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

        outputParcial << endl;
        outputParcial << "TEST MOVIMENT FITXA " << i + 1 << endl;
        outputParcial << "=====================" << endl;
        outputParcial << endl;
        string nomFitxer = nomFitxerInicial + to_string(i + 1) + ".txt";
        outputParcial << "Llegint estat del tauler del fitxer '" << nomFitxer << "'" << endl;
        outputParcial << "---------------" << endl;
    
        Tauler tauler;
        tauler.inicialitza(nomFitxer);
    
        outputParcial << "Contingut del tauler inicial: " << endl;
        char estatTaulerInicial[N_FILES_TAULER][N_COLUMNES_TAULER];
        llegeixTauler(nomFitxer, estatTaulerInicial);
        mostraTauler(estatTaulerInicial, outputParcial);
        outputParcial << "---------------" << endl;
        tauler.actualitzaMovimentsValids();
        outputParcial << "Executant moviment de posicio: " << posicioInicial[i] << " a posicio " << posicioFinal[i] << endl;
        outputParcial << comentariMoviment[i] << endl;
        outputParcial << "---------------" << endl;
        
        bool resultat = tauler.mouFitxa(Posicio(posicioInicial[i]), Posicio(posicioFinal[i]));

        outputParcial << "Resultat esperat del moviment: ";
        mostraBool(resultatEsperat[i], outputParcial);
        outputParcial << endl;
        outputParcial << "-------" << endl;
        outputParcial << "Contingut esperat del tauler despres del moviment: " << endl;
        char estatTaulerFinal[N_FILES_TAULER][N_COLUMNES_TAULER];
        llegeixTauler(nomFitxerFinal + to_string(i + 1) + ".txt", estatTaulerFinal);
        mostraTauler(estatTaulerFinal, outputParcial);
        outputParcial << "----------------" << endl;

        outputParcial << "Resultat obtingut del moviment: ";
        mostraBool(resultat, outputParcial);
        outputParcial << endl;
        outputParcial << "-------" << endl;
        outputParcial << "Contingut obtingut del tauler despres del moviment: " << endl;
        string estatTaulerResultat = tauler.toString();
        outputParcial << estatTaulerResultat << endl;
        outputParcial << "----------------" << endl;

        bool correcte = (resultatEsperat[i] == resultat) && comprovaTauler(estatTaulerFinal, estatTaulerResultat);
        if (correcte)
        {
            outputParcial << "CORRECTE" << endl;
            outputTest["status"] = "passed";
            grade += 0.3;
        }
        else
        {
            outputParcial << "ERROR" << endl;
            reduccio += 0.5;
            outputTest["status"] = "failed";
        }
    
        outputParcial << "-----------------------------------------------" << endl;
        
        cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");
    
        outputGeneral["score"] = grade;
        outputGeneral["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << outputGeneral << endl;
        jsonFile.close();
    }
    if (reduccio > 3.0)
        reduccio = 3.0;
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

	float reduccio = testLlegeixTauler(output);
    grade = grade + (1 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	reduccio = testMovimentsValids(output);
    grade = grade + (6 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	reduccio = testMovimentFitxa(output);
    grade = grade + (3 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

    return 0;
}