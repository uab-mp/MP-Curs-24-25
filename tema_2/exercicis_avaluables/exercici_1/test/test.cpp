#include "../source/vol.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using json = nlohmann::json;

void mostraBool(bool logic, stringstream& outputParcial)
{
	if (logic)
		outputParcial << "TRUE";
	else
		outputParcial << "FALSE";
}

void mostraPassatger(Passatger* p, stringstream& outputParcial)
{
	if (p == nullptr)
		outputParcial << "nullptr";
	else
		if (p->getDni() == "")
			outputParcial << "nullptr";
		else
			outputParcial << p->getDni() << ", " << p->getNom();
}


bool igualsPassatgers(Passatger* pObtingut, Passatger* pEsperat)
{
	bool iguals = false;
	if (pObtingut == nullptr)
	{
		if (pEsperat == nullptr)
			iguals = true;
		else
			if (pEsperat->getDni() == "")
				iguals = true;
	}
	else
		if (pEsperat != nullptr)
			iguals = (pObtingut->getDni() == pEsperat->getDni()) && (pObtingut->getNom() == pEsperat->getNom());
	return iguals;
}

float testSeient(json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = outputGeneral["score"];
	ofstream jsonFile;

	const int N_PROVES = 4;
	Passatger valorEsperat[N_PROVES] =
	{
		{ "dni_1", "nom_1" },
		{ "dni_1", "nom_1" },
		{ "", "" },
		{ "", "" }
	};
	bool resultatEsperat[N_PROVES] = { true, false, true, false };

	char operacio[N_PROVES] = { 'A', 'A', 'E', 'E' };
	Passatger dadesPassatger[N_PROVES] =
	{
		{ "dni_1", "nom_1" },
		{ "dni_2", "nom_2" },
		{ "", "" },
		{ "", "" }
	};

	json outputTest;
	stringstream outputParcial;

	outputTest =
	{
		{"name", "TEST INICIALITZACIO SEIENT "},
		{"visibility", "visible"},
		{"output", ""}
	};


	outputParcial << "Test inicialitaco de seient" << endl;
	outputParcial << "---------------------------" << endl;
	outputParcial << "Inicialitzant un seient amb codi 1A" << endl;
	Seient s("1A");

	outputParcial << " ---" << endl;
	outputParcial << " Valor esperat del passatger despres d'inicialitzar: ";
	mostraPassatger(nullptr, outputParcial);
	outputParcial << endl;
	outputParcial << " ---" << endl;
	outputParcial << " Valor obtingut del passatger despres d'inicialitzar: ";
	Passatger* p = s.getPassatger();
	mostraPassatger(p, outputParcial);
	outputParcial << endl; 
	outputParcial << " ---" << endl;
	if (!igualsPassatgers(p, nullptr))
	{
		outputParcial << " ERROR" << endl;
		outputTest["status"] = "failed";
		reduccio += 1.0;
	}
	else
	{
		outputParcial << " CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 0.4;
	}

	outputParcial << " ------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();

	int nTestAfegir = 0;
	int nTestEliminar = 0;

	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
		stringstream outputParcial;
	
		bool resultat;
		Passatger* p;
		if (operacio[i] == 'A')
		{
			nTestAfegir++;
			outputTest =
			{
				{"name", "TEST AFEGIR PASSATGER A SEIENT " + to_string(nTestAfegir)},
				{"visibility", "visible"},
				{"output", ""}
			};
			outputParcial << " TEST Afegir Passatger a seient " << nTestAfegir << endl;
			outputParcial << " ------------------------------" << endl;
			outputParcial << " Afegint passatger al seient..." << endl;
			outputParcial << " Dades del passatger: "; mostraPassatger(&dadesPassatger[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			outputParcial << " Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " Passatger esperat: "; mostraPassatger(&valorEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			resultat = s.assignaPassatger(dadesPassatger[i].getDni(), dadesPassatger[i].getNom());
			p = s.getPassatger();
			outputParcial << " Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
			outputParcial << " Passatger obtingut: "; mostraPassatger(p, outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
		}
		else
		{
			nTestEliminar++;
			outputTest =
			{
				{"name", "TEST ELIMINAR PASSATGER DE SEIENT " + to_string(nTestEliminar)},
				{"visibility", "visible"},
				{"output", ""}
			};
			outputParcial << " TEST Eliminar Passatger de seient " << nTestEliminar << endl;
			outputParcial << " ---------------------------------" << endl;
			outputParcial << " Eliminant el passatger del seient..." << endl;
			outputParcial << " ---" << endl;
			outputParcial << " Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " Passatger esperat: "; mostraPassatger(&valorEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			resultat = s.eliminaPassatger();
			p = s.getPassatger();
			outputParcial << " Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
			outputParcial << " Passatger obtingut: "; mostraPassatger(p, outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
		}

		if ((resultat == resultatEsperat[i]) && igualsPassatgers(p, &valorEsperat[i]))
		{
			outputParcial << " CORRECTE" << endl;
			outputTest["status"] = "passed";
			grade += 0.4;
			}			
		else
		{
			outputParcial << " ERROR" << endl;
			outputTest["status"] = "failed";
			reduccio += 1.0;
		}
		outputParcial << " ------------------------------------------" << endl;

		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");
	
		outputGeneral["score"] = grade;
		outputGeneral["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << outputGeneral << endl;
		jsonFile.close();
	}
	if (reduccio > 2.0)
		reduccio = 2.0;
	return reduccio;
}


float testVol(json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = outputGeneral["score"];
	ofstream jsonFile;
	json outputTest;
	stringstream outputParcial;
	
	const int N_SEIENTS = 6;
	string codisSeients[N_SEIENTS] = { "1A", "1B", "1C", "2A", "2B", "2C" };


	const int N_PROVES = 12;
	char operacio[N_PROVES] = { 'A', 'A', 'A', 'A', 'A', 'C', 'C', 'C', 'M', 'M', 'M', 'M' };
	Passatger dadesPassatger[N_PROVES] =
	{
		{ "dni_1", "nom_1" },
		{ "dni_2", "nom_2" },
		{ "dni_3", "nom_3" },
		{ "dni_4", "nom_4" },
		{ "dni_4", "nom_4" },
		{ "", "" },
		{ "", "" },
		{ "", "" },
		{ "", "" },
		{ "", "" },
		{ "", "" },
		{ "", "" }
	};
	string codiSeient[N_PROVES] = { "1A", "2C", "2A", "1A", "3A", "1A", "1B", "3C", "2C", "2A", "2B", "4A" };

	Passatger valorEsperat[N_PROVES] =
	{
		{ "dni_1", "nom_1" },
		{ "dni_2", "nom_2" },
		{ "dni_3", "nom_3" },
		{ "dni_1", "nom_1" },
		{ "", "" },
		{ "", "" },
		{ "", "" },
		{ "", "" },
		{ "", "" },
		{ "dni_3", "nom_3" },
		{ "", "" },
		{ "", "" }
	};
	bool resultatEsperat[N_PROVES] = { true, true, true, false, false, true, false, false, true, false, false, false };

	const int N_MODIFICACIONS = 4;
	string codiSeient2[N_MODIFICACIONS] = { "1B", "1B", "1B", "4B" };
	Passatger valorEsperat2[N_MODIFICACIONS] =
	{
		{ "dni_2", "nom_2" },
		{ "dni_2", "nom_2" },
		{ "dni_2", "nom_2" },
		{ "", "" }
	};

	outputTest =
	{
		{"name", "INICIALITZACIO DEL VOL "},
		{"visibility", "visible"},
		{"output", ""}
	};
	outputParcial << "Inicialitzacio del vol" << endl;
	outputParcial << "------------------------" << endl;
	outputParcial << " Inicialitzant els seients del vol (codis 1A, 1B, 1C, 2A, 2B, 2C)" << endl;
	outputParcial << "" << endl;
	Vol v("VOL_1", "ORIGEN", "DESTI", "DATA", "HORA", N_SEIENTS);
	v.afegeixSeients(codisSeients, N_SEIENTS);
	outputParcial << " ------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();

	int nTestAfegir = 0;
	int nTestEliminar = 0;
	int nTestModificar = 0;
	for (int i = 0; i < N_PROVES; i++)
	{
		bool resultat;
		Passatger* p;
		if (operacio[i] == 'A')
		{
			nTestAfegir++;
			outputTest =
			{
				{"name", "TEST AFEGIR PASSATGER AL VOL " + to_string(nTestAfegir)},
				{"visibility", "visible"},
				{"output", ""}
			};
			outputParcial << " TEST Afegir passatger al vol " << nTestAfegir << endl;
			outputParcial << " ----------------------------" << endl;
			outputParcial << " Afegint passatger a seient..." << endl;
			outputParcial << " Codi del seient: " << codiSeient[i] << endl;
			outputParcial << " Dades del passatger: "; mostraPassatger(&dadesPassatger[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			outputParcial << " Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " Passatger esperat al seient: "; mostraPassatger(&valorEsperat[i], outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			resultat = v.afegeixPassatger(codiSeient[i], dadesPassatger[i].getDni(), dadesPassatger[i].getNom());
			p = v.recuperaPassatger(codiSeient[i]);
			outputParcial << " Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
			outputParcial << " Passatger obtingut al seient: "; mostraPassatger(p, outputParcial); outputParcial << endl;
			outputParcial << " ---" << endl;
			if ((resultat == resultatEsperat[i]) && igualsPassatgers(p, &valorEsperat[i]))
			{
				outputParcial << " CORRECTE" << endl;
				outputTest["status"] = "passed";
				grade += 0.5;
			}
			else
			{
				outputParcial << " ERROR" << endl;
				outputTest["status"] = "failed";
				reduccio += 1.0;
			}
		}
		else
		{
			if (operacio[i] == 'C')
			{
				nTestEliminar++;
				outputTest =
				{
					{"name", "TEST ELIMINAR PASSATGER DEL VOL " + to_string(nTestEliminar)},
					{"visibility", "visible"},
					{"output", ""}
				};
				outputParcial << " TEST Eliminar passatger del vol " << nTestEliminar << endl;
				outputParcial << " -------------------------------" << endl;
				outputParcial << " Eliminant passatger de seient..." << endl;
				outputParcial << " Codi del seient: " << codiSeient[i] << endl;
				outputParcial << " ---" << endl;
				outputParcial << " Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
				outputParcial << " Passatger esperat al seient: "; mostraPassatger(&valorEsperat[i], outputParcial); outputParcial << endl;
				outputParcial << " ---" << endl;
				resultat = v.cancelaReserva(codiSeient[i]);
				p = v.recuperaPassatger(codiSeient[i]);
				outputParcial << " Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
				outputParcial << " Passatger obtingut al seient: "; mostraPassatger(p, outputParcial); outputParcial << endl;
				outputParcial << " ---" << endl;
				if ((resultat == resultatEsperat[i]) && igualsPassatgers(p, &valorEsperat[i]))
				{
					outputParcial << " CORRECTE" << endl;
					outputTest["status"] = "passed";
					grade += 0.5;
				}
				else
				{
					outputParcial << " ERROR" << endl;
					outputTest["status"] = "failed";
					reduccio += 1.0;
				}
			}
			else
			{
				nTestModificar++;
				outputTest =
				{
					{"name", "TEST MODIFICAR ASSIGNACIO DE SEIENT " + to_string(nTestModificar)},
					{"visibility", "visible"},
					{"output", ""}
				};
				outputParcial << " TEST Modificar assignacio de seient " << nTestModificar << endl;
				outputParcial << " -------------------------------" << endl;
				outputParcial << " Modificant assignacio de seient..." << endl;
				outputParcial << " Codi del seient original: " << codiSeient[i] << endl;
				outputParcial << " Codi del seient nou: " << codiSeient2[nTestModificar - 1] << endl;
				outputParcial << " ---" << endl;
				outputParcial << " Valor retorn esperat: "; mostraBool(resultatEsperat[i], outputParcial); outputParcial << endl;
				outputParcial << " Passatger esperat al seient original: "; mostraPassatger(&valorEsperat[i], outputParcial); outputParcial << endl;
				outputParcial << " Passatger esperat al seient nou: "; mostraPassatger(&valorEsperat2[nTestModificar - 1], outputParcial); outputParcial << endl;
				outputParcial << " ---" << endl;
				resultat = v.modificaReserva(codiSeient[i], codiSeient2[nTestModificar]);
				p = v.recuperaPassatger(codiSeient[i]);
				Passatger* p2 = v.recuperaPassatger(codiSeient2[nTestModificar - 1]);
				outputParcial << " Valor retorn obtingut: "; mostraBool(resultat, outputParcial); outputParcial << endl;
				outputParcial << " Passatger obtingut al seient original: "; mostraPassatger(p, outputParcial); outputParcial << endl;
				outputParcial << " Passatger obtingut al seient nou: "; mostraPassatger(p2, outputParcial); outputParcial << endl;
				outputParcial << " ---" << endl;
				if ((resultat == resultatEsperat[i]) && igualsPassatgers(p, &valorEsperat[i]) && igualsPassatgers(p2, &valorEsperat2[nTestModificar - 1]))
				{
					outputParcial << " CORRECTE" << endl;
					outputTest["status"] = "passed";
					grade += 0.5;
				}
				else
				{
					outputParcial << " ERROR" << endl;
					outputTest["status"] = "failed";
					reduccio += 1.0;
				}
			}
		}
		outputParcial << " ------------------------------------------" << endl;

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



float testOperadorAssignacio(json& outputGeneral)
{
	json outputTest;
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];
	float reduccio = 0.0;

	outputTest =
	{
		{"name", "TEST OPERADOR ASSIGNACIO"},
		{"visibility", "visible"},
		{"output", ""}
	};
	const int N_SEIENTS = 6;
	string codisSeients[N_SEIENTS] = { "1A", "1B", "1C", "2A", "2B", "2C" };

	outputParcial << "TEST Operador Assignacio" << endl;
	outputParcial << "-------------------------" << endl;
	outputParcial << "Creant un nou vol " << endl;
	outputParcial << "Inicialitzant els seients del vol (codis 1A, 1B, 1C, 2A, 2B, 2C)" << endl;
	outputParcial << "------" << endl;
	Vol* v = new Vol("VOL_1", "ORIGEN", "DESTI", "DATA", "HORA", N_SEIENTS);
	v->afegeixSeients(codisSeients, N_SEIENTS);
	outputParcial << "Afegint passatger amb 'dni_1', 'nom_1' al seient '2A'" << endl;
	bool resultat = v->afegeixPassatger("2A", "dni_1", "nom_1");
	outputParcial << "------" << endl;
	outputParcial << "Duplicant vol  amb l'operador d'assignacio" << endl;
	Vol nouVol;
	nouVol = *v;
	delete v;
	outputParcial << "Recuperant dades del vol duplicat" << endl;
	Passatger* p = nouVol.recuperaPassatger("2A");
	outputParcial << "Passatger al seient '2A': "; mostraPassatger(p, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	Passatger valorEsperat = { "dni_1", "nom_1" };
	if (igualsPassatgers(p, &valorEsperat))
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 1.0;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		outputTest["status"] = "failed";
		reduccio += 1.0;
	}
	outputParcial << "------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();

	return reduccio;
}



float testConstructorCopia(json& outputGeneral)
{
	json outputTest;
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];
	float reduccio = 0.0;

	outputTest =
	{
		{"name", "TEST CONSTRUCTOR COPIA"},
		{"visibility", "visible"},
		{"output", ""}
	};
	const int N_SEIENTS = 6;
	string codisSeients[N_SEIENTS] = { "1A", "1B", "1C", "2A", "2B", "2C" };

	outputParcial << "TEST Constructor de Copia" << endl;
	outputParcial << "-------------------------" << endl;
	outputParcial << "Creant un nou vol " << endl;
	outputParcial << "Inicialitzant els seients del vol (codis 1A, 1B, 1C, 2A, 2B, 2C)" << endl;
	outputParcial << "------" << endl;
	Vol* v = new Vol("VOL_1", "ORIGEN", "DESTI", "DATA", "HORA", N_SEIENTS);
	v->afegeixSeients(codisSeients, N_SEIENTS);
	outputParcial << "Afegint passatger amb 'dni_1', 'nom_1' al seient '2A'" << endl;
	bool resultat = v->afegeixPassatger("2A", "dni_1", "nom_1");
	outputParcial << "------" << endl;
	outputParcial << "Duplicant vol  amb el constructor de copia" << endl;
	Vol nouVol = *v;
	delete v;
	outputParcial << "Recuperant dades del vol duplicat" << endl;
	Passatger* p = nouVol.recuperaPassatger("2A");
	outputParcial << "Passatger al seient '2A': "; mostraPassatger(p, outputParcial); outputParcial << endl;
	outputParcial << "------" << endl;
	Passatger valorEsperat = { "dni_1", "nom_1" };
	if (igualsPassatgers(p, &valorEsperat))
	{
		outputParcial << "CORRECTE" << endl;
		outputTest["status"] = "passed";
		grade += 1.0;
	}
	else
	{
		outputParcial << "ERROR" << endl;
		outputTest["status"] = "failed";
		reduccio += 1.0;
	}
	outputParcial << "------------------------------------------" << endl;

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();

	return reduccio;
}


int main()
{
	float grade = 0.0;
	float reduccio;

    json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
  	output["stdout_visibility"] = "visible";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	

	cout << "Grade :=>> " << grade << endl;

	reduccio = testSeient(output);
	grade = grade + (2 - reduccio);
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();
	
	reduccio = testVol(output);
	grade = grade + (6 - reduccio);
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	reduccio = testConstructorCopia(output);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	reduccio = testOperadorAssignacio(output);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	if (grade == 10.0)
		cout << " Final del test sense errors" << endl;
	return 0;
}