#include "../source/joc.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using json = nlohmann::json;

float testMoviments(json& output)
{
	stringstream outputParcial;
	string outputFinal;
	ofstream jsonFile;

	float grade = 10.0;

	json outputTest =
	{
		{"name", "TEST COMPROVACIO MOVIMENTS PARTIDA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << endl;
	outputParcial << "TEST DE COMPROVACIO DELS MOVIMENTS DE LA PARTIDA" << endl;
	outputParcial << "------------------------------------------------" << endl;

	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	ifstream fitxerEsperat, fitxerObtingut;

	fitxerEsperat.open("llistat_moviments_resultat.txt");
	if (fitxerEsperat.is_open())
	{
		fitxerObtingut.open("llistat_moviments.txt");
		if (fitxerObtingut.is_open())
		{
			int jugadorEsperat, accioEsperada, colorEsperat, valorEsperat;
			int jugadorObtingut, accioObtinguda, colorObtingut, valorObtingut;
			fitxerEsperat >> jugadorEsperat >> accioEsperada >> colorEsperat >> valorEsperat;
			while (!fitxerEsperat.eof())
			{
				outputParcial << "Moviment Esperat:  " << "Jugador: " << jugadorEsperat;
				if (accioEsperada == 0)
					outputParcial << " TIRA CARTA ";
				else
					if (accioEsperada == 1)
						outputParcial << " ROBA CARTA ";
				outputParcial << "Color: " << colorEsperat << " Valor: " << valorEsperat << endl;
				outputParcial << "------" << endl;

				fitxerObtingut >> jugadorObtingut >> accioObtinguda >> colorObtingut >> valorObtingut;
				if (!fitxerObtingut.eof())
				{
					outputParcial << "Moviment Obtingut:  " << "Jugador: " << jugadorObtingut;
					if (accioObtinguda == 0)
						outputParcial << " TIRA CARTA ";
					else
						if (accioObtinguda == 1)
							outputParcial << " ROBA CARTA ";
					outputParcial << "Color: " << colorObtingut << " Valor: " << valorObtingut << endl;
					outputParcial << "------" << endl;
					if ((jugadorEsperat == jugadorObtingut) && (accioEsperada == accioObtinguda) &&
						(colorEsperat == colorObtingut) && (valorEsperat == valorObtingut))
						outputParcial << "CORRECTE" << endl;
					else
					{
						outputParcial << "ERROR" << endl;
						grade -= 0, 5;
					}
					outputParcial << "---------------------------------" << endl;
				}
				else
				{
					outputParcial << "ERROR. No hi ha mes moviments al fitxer resultat de la partida" << endl;
					grade -= 5.0;
				}
				cout << outputParcial.str();
				outputFinal += outputParcial.str();
				outputParcial.str("");

				fitxerEsperat >> jugadorEsperat >> accioEsperada >> colorEsperat >> valorEsperat;
			}
			fitxerObtingut >> jugadorObtingut >> accioObtinguda >> colorObtingut >> colorObtingut;
			if (!fitxerObtingut.eof())
			{
				outputParcial << "ERROR. Hi ha mes moviments dels esperats al fitxer resultat de la partida" << endl;
				grade -= 5.0;
			}

			fitxerObtingut.close();
		}
		else
		{
			outputParcial << "ERROR. No es pot obrir fitxer amb el resultat de la partida" << endl;
			grade = 0.0;
		}

		fitxerEsperat.close();
	}
	else
	{
		outputParcial << "ERROR. No es pot obrir fitxer amb el resultat esperat" << endl;
		grade = 0.0;
	}

	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	
	if (grade < 0)
		grade = 0.0;

	if (grade == 10.0)
		outputTest["status"] = "passed";
	else
		outputTest["status"] = "failed";

	outputTest["output"] = outputFinal;
	output["score"] = grade;
	output["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	cout << endl << "Grade :=>> " << grade << endl << endl;

	return grade;
}


int main()
{
	float grade = 0;
	json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
	output["stdout_visibility"] = "visible";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	cout << endl << "Grade :=>> " << grade << endl << endl;

	Joc partida;

	json outputTest =
	{
		{"name", "EXECUCIO DE LA PARTIDA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	stringstream outputParcial;

	outputParcial << endl;
	outputParcial << "INICIALITZACIO DEL TEST: Execucio de la partida completa" << endl;
	outputParcial << "--------------------------------------------------------" << endl;
	outputParcial << endl;
	outputParcial << "Executant la partida a partir del fitxer cartes.txt" << endl;
	outputParcial << "Guardant els moviments al fitxer llista_moviments.txt" << endl;
	outputParcial << "......." << endl;
	outputParcial << endl;

	partida.inicialitza("cartes_inicial.txt", 4);
	while (!partida.final())
		partida.fesMoviment();
	partida.guarda("llistat_moviments.txt");

	outputParcial << "Partida finalitzada" << endl;
	outputParcial << "------------------------------------------------------" << endl;
	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	output["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	grade = testMoviments(output);

	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}
