#include "../source/empresa.h"
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

void inicialitzaTestComanda(Comanda& comanda, json& outputGeneral)
{
	ofstream jsonFile;
	json outputTest;
	stringstream outputParcial;

	outputTest =
	{
		{"name", "INICIALITZACIO TEST CLASSE COMANDA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "INICIALITZACIO DEL TEST DE LA CLASSE COMANDA" << endl;
	outputParcial << "--------------------------------------------" << endl;
	outputParcial << endl;
	outputParcial << "Cridant al constructor de Comandes per inicialitzar dades de la comanda" << endl;
	outputParcial << "-----------------------------------------------------------------------" << endl;
	outputParcial << "Nom del client: client_1" << endl;
	outputParcial << "Data de la comanda: 01/01/2018" << endl;
	outputParcial << "Num. productes: 4" << endl;

	const int NPROVES = 4;
	string codiTest[NPROVES] = { "prod_1", "prod_2", "prod_3", "prod_4" };
	int nUnitatsTest[NPROVES] = { 1, 10, 20, 1 };
	float preuTest[NPROVES] = { 100.0, 5.0, 10.0, 20.0 };

	outputParcial << "------------" << endl;
	outputParcial << endl;
	outputParcial << "Afegint productes a la comanda amb el metode AFEGEIX_PRODUCTE" << endl;
	outputParcial << "-------------------------------------------------------------" << endl;

	for (int p = 0; p < NPROVES; p++)
	{
		outputParcial << "Codi Producte: " << codiTest[p] << endl;
		outputParcial << "Num. unitats: " << nUnitatsTest[p] << endl;
		outputParcial << "Preu unitat: " << preuTest[p] << endl;
		comanda.afegeixProducte(codiTest[p], nUnitatsTest[p], preuTest[p]);
		outputParcial << "----------------" << endl;
	}
	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();
}

void testConsultaProducte(Comanda& comanda, json& outputGeneral)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];
	
	const int NPROVES = 5;

	string codiTest[NPROVES] = { "prod_1", "prod_2", "prod_3", "prod_4", "prod_5" };
	int nUnitatsTest[NPROVES] = { 1, 10, 20, 1, 0 };
	float preuTest[NPROVES] = { 100.0, 5.0, 10.0, 20.0, 0.0 };
	bool validTest[NPROVES] = { true, true, true, true, false };

	for (int p = 0; p < NPROVES; p++)
	{
		float localGrade = 0.0;
		json outputTest =
		{
			{"name", "TEST COMANDA - CONSULTA PRODUCTE - TEST " + to_string(p + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};
		outputParcial << "TEST CONSULTA PRODUCTES DE COMANDA " << p + 1 << endl;
		outputParcial << "----------------------------------" << endl;
		outputParcial << "Codi Producte a consultar: " << codiTest[p] << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTest[p], outputParcial); outputParcial << endl;
		if (validTest[p])
		{
			outputParcial << "Num. unitats esperat: " << nUnitatsTest[p] << endl;
			outputParcial << "Preu unitat esperat: " << preuTest[p] << endl;
		}
		outputParcial << "------" << endl;
		int nUnitats;
		float preu;
		bool valid = comanda.consultaProducte(codiTest[p], nUnitats, preu);
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		if (valid)
		{
			outputParcial << "Num. unitats obtingut: " << nUnitats << endl;
			outputParcial << "Preu unitat obtingut: " << preu << endl;
		}
		outputParcial << "------" << endl;
		if (valid == validTest[p])
		{
			if (valid)
				if ((nUnitats == nUnitatsTest[p]) &&
					(fabs(preu - preuTest[p]) < 0.1))
				{
					outputParcial << "CORRECTE" << endl;
					localGrade += 0.2;
				}					
				else
				{
					outputParcial << "ERROR" << endl;
				}
			else
			{
				outputParcial << "CORRECTE" << endl;
				localGrade += 0.2;
			}				
		}
		else
		{
			outputParcial << "ERROR" << endl;
		}
		outputParcial << "------------------------------------------" << endl;

		if (localGrade > 0)
			outputTest["status"] = "passed";
		else
			outputTest["status"] = "failed";

		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		grade += localGrade;
		outputGeneral["score"] = grade;
		outputGeneral["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << outputGeneral << endl;
		jsonFile.close();
		cout << endl << "Grade :=>> " << grade << endl << endl;

	}
}

void testEliminaProducte(Comanda& comanda, json& outputGeneral)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];

	const int NPROVES = 4;

	string codiTest[NPROVES] = { "prod_2", "prod_1", "prod_4", "prod_5" };
	bool validTest[NPROVES] = { true, true, true, false };

	for (int p = 0; p < NPROVES; p++)
	{
		float localGrade = 0.0;
		json outputTest =
		{
			{"name", "TEST COMANDA - ELIMINA PRODUCTE - TEST " + to_string(p + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};		
		outputParcial << "TEST ELIMINA PRODUCTE DE COMANDA" << p + 1 << endl;
		outputParcial << "--------------------------------" << endl;
		outputParcial << "Codi Producte a eliminar: " << codiTest[p] << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTest[p], outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;
		bool valid = comanda.eliminaProducte(codiTest[p]);
		bool trobat;
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;
		if (valid)
		{
			outputParcial << "Fent consulta del producte eliminat... " << endl;
			int nUnitats;
			float preu;
			trobat = comanda.consultaProducte(codiTest[p], nUnitats, preu);
			if (trobat)
				outputParcial << "Producte trobat" << endl;
			else
				outputParcial << "Producte NO trobat " << endl;
			outputParcial << "------" << endl;
		}
		if (valid == validTest[p])
		{
			if (valid)
				if (!trobat)
				{
					outputParcial << "CORRECTE" << endl;
					localGrade += 0.25;
				}
				else
				{
					outputParcial << "ERROR" << endl;
				}
			else
			{
				outputParcial << "CORRECTE" << endl;
				localGrade += 0.25;
			}
		}
		else
		{
			outputParcial << "ERROR" << endl;
		}
		outputParcial << "------------------------------------------" << endl;
		if (localGrade > 0)
			outputTest["status"] = "passed";
		else
			outputTest["status"] = "failed";

		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		grade += localGrade;
		outputGeneral["score"] = grade;
		outputGeneral["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << outputGeneral << endl;
		jsonFile.close();
		cout << endl << "Grade :=>> " << grade << endl << endl;
	}
}

void testConsulta(Comanda& comanda, json& outputGeneral)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];
	float localGrade = 0.0;

	json outputTest =
	{
		{"name", "TEST CONSULTA DADES COMANDA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST CONSULTA DADES COMANDA" << endl;
	outputParcial << "---------------------------" << endl;

	outputParcial << "Nom del client esperat: client_1" << endl;
	outputParcial << "Data de la comanda esperada: 01/01/2018" << endl;
	outputParcial << "Import esperat: 370.0" << endl;

	outputParcial << "------" << endl;

	outputParcial << "Nom del client obtingut: " << comanda.getClient() << endl;
	string data = comanda.getData();
	outputParcial << "Data de la comanda obtinguda: " << data << endl;
	outputParcial << "------" << endl;
	outputParcial << "Import obtingut: " << comanda.getImport() << endl;

	if ((comanda.getClient() == "client_1") && (data == "01/01/2018") &&
		(fabs(comanda.getImport() - 370.0) < 0.1))
	{
		outputParcial << "CORRECTE" << endl;
		localGrade += 0.5;
	}		
	else
	{
		outputParcial << "ERROR" << endl;
	}
	outputParcial << "------------------------------------------" << endl;
	if (localGrade > 0)
		outputTest["status"] = "passed";
	else
		outputTest["status"] = "failed";

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	grade += localGrade;
	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();
	cout << endl << "Grade :=>> " << grade << endl << endl;
}


void testConstructorCopia(Comanda& comanda, json& outputGeneral)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];

	json outputTest =
	{
		{"name", "TEST CONSTRUCTOR COPIA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST CONSTRUCTOR COPIA" << endl;
	outputParcial << "----------------------" << endl;

	outputParcial << "Inicialitzant nou objecte Comanda amb constructor de copia....." << endl;

	Comanda copia(comanda);

	outputParcial << "Comprovant dades de la Comanda creada amb el constructor de copia....." << endl;
	outputParcial << "------" << endl;
	outputParcial << "Nom del client esperat: client_1" << endl;
	outputParcial << "Data de la comanda esperada: 01/01/2018" << endl;
	outputParcial << "Import esperat: 370.0" << endl;
	outputParcial << "------" << endl;
	outputParcial << "Nom del client obtingut: " << comanda.getClient() << endl;
	string data = comanda.getData();
	outputParcial << "Data de la comanda obtinguda: " << data << endl;
	outputParcial << "Import obtingut: " << comanda.getImport() << endl;
	outputParcial << "------" << endl;

	bool correcte = true;
	if ((comanda.getClient() != "client_1") || (data != "01/01/2018") ||
		(fabs(comanda.getImport() - 370.0) > 0.1))
	{
		correcte = false;
		outputParcial << "ERROR" << endl;
	}
	else
		outputParcial << "CORRECTE" << endl;
	outputParcial << "------" << endl;
		
	outputParcial << "Comprovant producTes de la Comanda creada amb el constructor de copia....." << endl;
	outputParcial << "------" << endl;
	const int NPROVES = 4;
	string codiTest[NPROVES] = { "prod_1", "prod_2", "prod_3", "prod_4"};
	int nUnitatsTest[NPROVES] = { 1, 10, 20, 1};
	float preuTest[NPROVES] = { 100.0, 5.0, 10.0, 20.0};

	for (int p = 0; p < NPROVES; p++)
	{
		outputParcial << "Codi Producte: " << codiTest[p] << endl;
		outputParcial << "Num. unitats esperat: " << nUnitatsTest[p] << endl;
		outputParcial << "Preu unitat esperat: " << preuTest[p] << endl;
		outputParcial << "------" << endl;
		int nUnitats;
		float preu;
		bool valid = comanda.consultaProducte(codiTest[p], nUnitats, preu);
		outputParcial << "Num. unitats obtingut: " << nUnitats << endl;
		outputParcial << "Preu unitat obtingut: " << preu << endl;
		outputParcial << "------" << endl;
		if ((nUnitats != nUnitatsTest[p]) &&
			(fabs(preu - preuTest[p]) > 0.1))
		{
			correcte = false;
			outputParcial << "ERROR" << endl;
		}
		else
			outputParcial << "CORRECTE" << endl;
		outputParcial << "------" << endl;
	}
	outputParcial << "------------------------------------------" << endl;
	if (correcte)
	{ 
		outputTest["status"] = "passed";
		grade += 0.75;
	}
	else
		outputTest["status"] = "failed";

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();
	cout << endl << "Grade :=>> " << grade << endl << endl;
}

void testOperadorAssignacio(Comanda& comanda, json& outputGeneral)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];

	json outputTest =
	{
		{"name", "TEST OPERADOR ASSIGNACIO"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST OPERADOR ASSIGNACIO" << endl;
	outputParcial << "------------------------" << endl;

	outputParcial << endl << "Inicialitzant nou objecte Comanda amb operador assignacio....." << endl;

	Comanda assignacio("", "01/01/2018", 3);

	assignacio = comanda;

	outputParcial << "Comprovant dades de la Comanda inicialitzada amb l'operador d'assignacio....." << endl;
	outputParcial << "------" << endl;
	outputParcial << "Nom del client esperat: client_1" << endl;
	outputParcial << "Data de la comanda esperada: 01/01/2018" << endl;
	outputParcial << "Import esperat: 370.0" << endl;
	outputParcial << "------" << endl;
	outputParcial << "Nom del client obtingut: " << comanda.getClient() << endl;
	string data = comanda.getData();
	outputParcial << "Data de la comanda obtinguda: " << data << endl;
	outputParcial << "Import obtingut: " << comanda.getImport() << endl;
	outputParcial << "------" << endl;

	bool correcte = true;
	if ((comanda.getClient() != "client_1") || (data != "01/01/2018") ||
		(fabs(comanda.getImport() - 370.0) > 0.1))
	{
		correcte = false;
		outputParcial << "ERROR" << endl;
	}
	else
		outputParcial << "CORRECTE" << endl;
	outputParcial << "------" << endl;

	outputParcial << "Comprovant producTes de la Comanda inicialitzada amb l'operador d'assignacio....." << endl;
	outputParcial << "------" << endl;
	const int NPROVES = 4;
	string codiTest[NPROVES] = { "prod_1", "prod_2", "prod_3", "prod_4" };
	int nUnitatsTest[NPROVES] = { 1, 10, 20, 1 };
	float preuTest[NPROVES] = { 100.0, 5.0, 10.0, 20.0 };

	for (int p = 0; p < NPROVES; p++)
	{
		outputParcial << "Codi Producte: " << codiTest[p] << endl;
		outputParcial << "Num. unitats esperat: " << nUnitatsTest[p] << endl;
		outputParcial << "Preu unitat esperat: " << preuTest[p] << endl;
		outputParcial << "------" << endl;
		int nUnitats;
		float preu;
		bool valid = comanda.consultaProducte(codiTest[p], nUnitats, preu);
		outputParcial << "Num. unitats obtingut: " << nUnitats << endl;
		outputParcial << "Preu unitat obtingut: " << preu << endl;
		outputParcial << "------" << endl;
		if ((nUnitats != nUnitatsTest[p]) &&
			(fabs(preu - preuTest[p]) > 0.1))
		{
			correcte = false;
			outputParcial << "ERROR" << endl;
		}
		else
			outputParcial << "CORRECTE" << endl;
		outputParcial << "------" << endl;
	}
	outputParcial << "------------------------------------------" << endl;
	if (correcte)
	{
		outputTest["status"] = "passed";
		grade += 0.75;
	}
	else
		outputTest["status"] = "failed";

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();
	cout << endl << "Grade :=>> " << grade << endl << endl;
}

void inicialitzaTestEmpresa(Empresa& empresa, json& outputGeneral)
{
	ofstream jsonFile;
	json outputTest;
	stringstream outputParcial;

	outputTest =
	{
		{"name", "INICIALITZACIO TEST CLASSE EMPRESA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "INICIALITZACIO DEL TEST DE LA CLASSE EMPRESA" << endl;
	outputParcial << "--------------------------------------------" << endl;
	outputParcial << endl;
	outputParcial << "Llegint fitxer 'productes.txt' per inicialitzar dades dels productes..." << endl;
	outputParcial << "-----------------------------------------------------------------------" << endl;
	empresa.llegeixProductes("productes.txt");

	outputParcial << endl;
	outputParcial << "Afegint comanda del fitxer 'comanda_1.txt..." << endl;
	outputParcial << "--------------------------------------------" << endl;
	empresa.afegeixComanda("comanda_1.txt");

	outputParcial << endl;
	outputParcial << "Afegint comanda del fitxer 'comanda_2.txt..." << endl;
	outputParcial << "--------------------------------------------" << endl;
	empresa.afegeixComanda("comanda_2.txt");

	outputParcial << endl;
	outputParcial << "Afegint comanda del fitxer 'comanda_3.txt..." << endl;
	outputParcial << "--------------------------------------------" << endl;
	empresa.afegeixComanda("comanda_3.txt");

	outputParcial << endl;
	outputParcial << "Afegint comanda del fitxer 'comanda_4.txt..." << endl;
	outputParcial << "--------------------------------------------" << endl;
	empresa.afegeixComanda("comanda_4.txt");
	outputParcial << endl;

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();
}

void testDadesComanda(Empresa& e, json& outputGeneral)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];

	const int NPROVES_COMANDA = 5;
	const int NPROVES_PRODUCTE = 3;

	string nomClientTest[NPROVES_COMANDA] = { "NOM_CLIENT_1", "NOM_CLIENT_1", "NOM_CLIENT_2", "NOM_CLIENT_3", "NOM_CLIENT_4" };
	string dataTest[NPROVES_COMANDA] = 
	{
		"01/01/2018",
		"01/02/2018",
		"01/02/2018",
		"01/03/2018",
		"01/01/2018" 
	};
	float importTest[NPROVES_COMANDA] = { 5000, 0.0, 1400, 0.0, 0.0 };
	int nProvesProducteTest[NPROVES_COMANDA] = { 3, 1, 3, 0, 0 };
	string codiProducteTest[NPROVES_COMANDA][NPROVES_PRODUCTE] = 
	{
		{ "CODI_PROD_1", "CODI_PROD_2", "CODI_PROD_3" },
		{ "CODI_PROD_1" },
		{ "CODI_PROD_1", "CODI_PROD_2", "CODI_PROD_4" },
		{},
		{}
	};
	int nUnitatsTest[NPROVES_COMANDA][NPROVES_PRODUCTE] =
	{
		{10, 20, 0},
		{10},
		{1, 2, 0},
		{},
		{}
	};
	float preuTest[NPROVES_COMANDA][NPROVES_PRODUCTE] =
	{
		{ 100, 200, 0 },
		{ 100 },
		{ 100, 200, 0 },
		{},
		{}
	};
	bool validTestComanda[NPROVES_COMANDA] = { true, false, true, false, false };
	bool validTestProducte[NPROVES_COMANDA][NPROVES_PRODUCTE] =
	{
		{true, true, false},
		{false},
		{ true, true, false },
		{},
		{}
	};

	for (int p = 0; p < NPROVES_COMANDA; p++)
	{
		float reduccio = 0.0;
		json outputTest =
		{
			{"name", "TEST EMPRESA - CONSULTA DADES COMANDA - TEST " + to_string(p + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST CLASSE EMPRESA: CONSULTA DADES COMANDA " << p + 1 << endl;
		outputParcial << "-----------------------------------------------" << endl;
		outputParcial << "Nom Client: " << nomClientTest[p] << endl;
		outputParcial << "DataComanda: " << dataTest[p] << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTestComanda[p], outputParcial); outputParcial << endl;
		if (validTestComanda[p])
			outputParcial << "Import esperat: " << importTest[p] << endl;
		outputParcial << "------" << endl;
		float import;
		bool valid = e.importComanda(nomClientTest[p], dataTest[p], import);
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		if (valid)
			outputParcial << "Import obtingut: " << import << endl;
		outputParcial << "------" << endl;
		if (valid == validTestComanda[p])
		{
			if (valid)
				if (fabs(import- importTest[p]) < 0.1)
					outputParcial << "CORRECTE" << endl;
				else
				{
					outputParcial << "ERROR" << endl;
					reduccio += 0.5;
				}
			else
				outputParcial << "CORRECTE" << endl;
		}
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		outputParcial << "------" << endl;
		outputParcial << "Consulta dels productes de la comanda" << endl;
		outputParcial << "-------------------------------------" << endl;
		for (int i = 0; i < nProvesProducteTest[p]; i++)
		{
			outputParcial << "Codi Producte: " << codiProducteTest[p][i] << endl;
			outputParcial << "------" << endl;
			outputParcial << "Valor retorn esperat: "; mostraBool(validTestProducte[p][i], outputParcial); outputParcial << endl;
			if (validTestProducte[p][i])
			{
				outputParcial << "Num. unitats esperat: " << nUnitatsTest[p][i] << endl;
				outputParcial << "Preu esperat: " << preuTest[p][i] << endl;
			}
			outputParcial << "------" << endl;
			float preu;
			int nUnitats;
			bool valid = e.DetallProducteComanda(nomClientTest[p], dataTest[p], codiProducteTest[p][i], nUnitats, preu);
			outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
			if (valid)
			{
				outputParcial << "Num. unitats obtingut: " << nUnitats << endl;
				outputParcial << "Preu obtingut: " << preu << endl;
			}
			outputParcial << "------" << endl;
			if (valid == validTestProducte[p][i])
			{
				if (valid)
					if ((nUnitats == nUnitatsTest[p][i]) && (fabs(preu - preuTest[p][i]) < 0.1))
					outputParcial << "CORRECTE" << endl;
					else
					{
						outputParcial << "ERROR" << endl;
						reduccio += 0.5;
					}
				else
					outputParcial << "CORRECTE" << endl;
			}
			else
			{
				outputParcial << "ERROR" << endl;
				reduccio += 0.5;
			}
			outputParcial << "------" << endl;

		}
		if (reduccio > 0)
			outputTest["status"] = "failed";
		else
			outputTest["status"] = "passed";

		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		if (reduccio > 0.5)
			reduccio = 0.5;
		grade += (0.8 - reduccio);
		outputGeneral["score"] = grade;
		outputGeneral["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << outputGeneral << endl;
		jsonFile.close();
		cout << endl << "Grade :=>> " << grade << endl << endl;
	}
}


void testEliminaComanda(Empresa& e, json& outputGeneral)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = outputGeneral["score"];

	json outputTest =
	{
		{"name", "TEST ELIMINA COMANDA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST ELIMINA COMANDA" << endl;
	outputParcial << "--------------------" << endl;
	outputParcial << "Eliminant comanda del client NOM_CLIENT_2 i data 01/02/2018..." << endl;
	e.eliminaComanda("NOM_CLIENT_2", "01/02/2018");
	outputParcial << "Eliminant comanda del client NOM_CLIENT_4 i data 01/03/2018..." << endl;
	e.eliminaComanda("NOM_CLIENT_4", "01/03/2018");
	outputParcial << "Intentant eliminar comanda que no existeix, del client NOM_CLIENT_1 i data 01/03/2018..." << endl;
	e.eliminaComanda("NOM_CLIENT_1", "01/03/2018");
	outputParcial << "------" << endl;
	outputParcial << "Comprovant dades de les comandes existents despres d'eliminar..." << endl;
	outputParcial << "------" << endl;


	const int NPROVES_COMANDA = 3;
	const int NPROVES_PRODUCTE = 3;

	string nomClientTest[NPROVES_COMANDA] = { "NOM_CLIENT_1", "NOM_CLIENT_2", "NOM_CLIENT_4"};
	string dataTest[NPROVES_COMANDA] =
	{
		"01/01/2018",
		"01/02/2018",
		"01/03/2018"
	};
	float importTest[NPROVES_COMANDA] = { 5000, 0, 0};
	int nProvesProducteTest[NPROVES_COMANDA] = { 2, 0, 0};
	string codiProducteTest[NPROVES_COMANDA][NPROVES_PRODUCTE] =
	{
		{ "CODI_PROD_1", "CODI_PROD_2"},
		{ },
		{ }
	};
	int nUnitatsTest[NPROVES_COMANDA][NPROVES_PRODUCTE] =
	{
		{10, 20},
		{},
		{}
	};
	float preuTest[NPROVES_COMANDA][NPROVES_PRODUCTE] =
	{
		{ 100, 200 },
		{ },
		{ }
	};
	bool validTestComanda[NPROVES_COMANDA] = { true, false, false};
	bool validTestProducte[NPROVES_COMANDA][NPROVES_PRODUCTE] =
	{
		{true, true},
		{},
		{}
	};

	float reduccio = 0.0;
	for (int p = 0; p < NPROVES_COMANDA; p++)
	{
		outputParcial << "CONSULTA DADES COMANDA "<< endl;
		outputParcial << "----------------------" << endl;
		outputParcial << "Nom Client: " << nomClientTest[p] << endl;
		outputParcial << "Data Comanda: " << dataTest[p] << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTestComanda[p], outputParcial); outputParcial << endl;
		if (validTestComanda[p])
			outputParcial << "Import esperat: " << importTest[p] << endl;
		outputParcial << "------" << endl;
		float import;
		bool valid = e.importComanda(nomClientTest[p], dataTest[p], import);
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		if (valid)
			outputParcial << "Import obtingut: " << import << endl;
		outputParcial << "------" << endl;
		if (valid == validTestComanda[p])
		{
			if (valid)
				if (fabs(import - importTest[p]) < 0.1)
					outputParcial << "CORRECTE" << endl;
				else
				{
					outputParcial << "ERROR" << endl;
					reduccio += 1.0;
				}
			else
				outputParcial << "CORRECTE" << endl;
		}
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "------" << endl;
		outputParcial << "Consulta dels productes de la comanda" << endl;
		outputParcial << "-------------------------------------" << endl;
		for (int i = 0; i < nProvesProducteTest[p]; i++)
		{
			outputParcial << "Codi Producte: " << codiProducteTest[p][i] << endl;
			outputParcial << "------" << endl;
			outputParcial << "Valor retorn esperat: "; mostraBool(validTestProducte[p][i], outputParcial); outputParcial << endl;
			if (validTestProducte[p][i])
			{
				outputParcial << "Num. unitats esperat: " << nUnitatsTest[p][i] << endl;
				outputParcial << "Preu esperat: " << preuTest[p][i] << endl;
			}
			outputParcial << "------" << endl;
			float preu;
			int nUnitats;
			bool valid = e.DetallProducteComanda(nomClientTest[p], dataTest[p], codiProducteTest[p][i], nUnitats, preu);
			outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
			if (valid)
			{
				outputParcial << "Num. unitats obtingut: " << nUnitats << endl;
				outputParcial << "Preu obtingut: " << preu << endl;
			}
			outputParcial << "------" << endl;
			if (valid == validTestProducte[p][i])
			{
				if (valid)
					if ((nUnitats == nUnitatsTest[p][i]) && (fabs(preu - preuTest[p][i]) < 0.1))
						outputParcial << "CORRECTE" << endl;
					else
					{
						outputParcial << "ERROR" << endl;
						reduccio += 1.0;
					}
				else
					outputParcial << "CORRECTE" << endl;
			}
			else
			{
				outputParcial << "ERROR" << endl;
				reduccio += 1.0;
			}
			outputParcial << "------" << endl;

		}

	}
	if (reduccio > 0)
		outputTest["status"] = "failed";
	else
		outputTest["status"] = "passed";

	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	if (reduccio > 2.0)
		reduccio = 2.0;
	grade += (2.0 - reduccio);
	outputGeneral["score"] = grade;
	outputGeneral["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << outputGeneral << endl;
	jsonFile.close();
	cout << endl << "Grade :=>> " << grade << endl << endl;
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

	cout << endl << "Grade :=>> " << grade << endl << endl;

	string data("01/01/2018");
	Comanda comanda("client_1", data, 4);
	inicialitzaTestComanda(comanda, output);

	testConsulta(comanda, output);
	testConsultaProducte(comanda, output);
	testConstructorCopia(comanda, output);
	testOperadorAssignacio(comanda, output);
	testEliminaProducte(comanda, output);


	Empresa e;
	inicialitzaTestEmpresa(e, output);

	testDadesComanda(e, output);
	testEliminaComanda(e, output);

	grade = output["score"];
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}