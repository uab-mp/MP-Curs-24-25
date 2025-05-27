#include "../source/reserves_hotel.h"
#include <math.h>
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

void testNReservesDia(ReservesHotel& reserves, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int NPROVES = 7;

	Data dataTest[NPROVES] =
	{
		{ 1, 1, 2018 },
		{ 2, 1, 2018 },
		{ 3, 1, 2018 },
		{ 4, 1, 2018 },
		{ 5, 1, 2018 },
		{ 6, 1, 2018 },
		{ 31, 12, 2017 },
	};

	int nHabitacionsTest[NPROVES] = { 2, 3, 8, 8, 2, 0, 0 };

	for (int p = 0; p < NPROVES; p++)
	{
		json outputTest =
		{
			{"name", "TEST N RESERVES DIA " + to_string(p + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST N RESERVES DIA  " << p + 1 << endl;
		outputParcial << "---------------------" << endl;
		outputParcial << "Data: " << dataTest[p].getDia() << "/" << dataTest[p].getMes() << "/" << dataTest[p].getAny() << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: " << nHabitacionsTest[p] << endl;
		outputParcial << "------" << endl;
		int nHabitacions = reserves.nReservesDia(dataTest[p]);
		outputParcial << "Valor retorn obtingut: " << nHabitacions << endl;
		outputParcial << "------" << endl;
		if (nHabitacions == nHabitacionsTest[p])
		{
			outputParcial << "CORRECTE" << endl;
			outputTest["status"] = "passed";
			grade += 0.2;
		}
		else
		{
			outputParcial << "ERROR" << endl;
			outputTest["status"] = "failed";
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		output["score"] = grade;
		output["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << output << endl;
		jsonFile.close();
		cout << endl << "Grade :=>> " << grade << endl << endl;
	}
}


void testAfegeixReserva(ReservesHotel& reserves, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int NPROVES = 5;

	string nomTest[NPROVES] = { "client_a", "client_b", "client_c", "client_d", "client_e" };
	Data dataTest[NPROVES] =
	{
		{ 1, 1, 2018 },
		{ 2, 1, 2018 },
		{ 3, 1, 2018 },
		{ 4, 1, 2018 },
		{ 5, 1, 2018 },
	};
	int nDiesTest[NPROVES] = { 2, 3, 2, 4, 2 };
	int nHabitacionsTest[NPROVES] = { 2, 3, 1, 3, 2 };
	bool validTest[NPROVES] = { true, false, true, false, true };

	for (int p = 0; p < NPROVES; p++)
	{
		json outputTest =
		{
			{"name", "TEST AFEGEIX RESERVA " + to_string(p + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST AFEGEIX RESERVA " << p + 1 << endl;
		outputParcial << "----------------------" << endl;
		outputParcial << "Nom Client: " << nomTest[p] << endl;
		outputParcial << "Data Entrada: " << dataTest[p].getDia() << "/" << dataTest[p].getMes() << "/" << dataTest[p].getAny() << endl;
		outputParcial << "Num. dies: " << nDiesTest[p] << endl;
		outputParcial << "Num. habitacions: " << nHabitacionsTest[p] << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTest[p], outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;
		bool valid = reserves.afegeixReserva(nomTest[p], dataTest[p], nDiesTest[p], nHabitacionsTest[p]);
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		outputParcial << "------" << endl;
		if (valid == validTest[p])
		{
			outputParcial << "CORRECTE" << endl;
			outputTest["status"] = "passed";
			grade += 0.3;
		}
		else
		{
			outputParcial << "ERROR" << endl;
			outputTest["status"] = "failed";
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		output["score"] = grade;
		output["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << output << endl;
		jsonFile.close();
		cout << endl << "Grade :=>> " << grade << endl << endl;
	}
}

void testConsultaReserva(ReservesHotel& reserves, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	const int NPROVES = 7;

	string nomTest[NPROVES] = { "CLIENT_2", "client_a", "CLIENT_7", "client_b", "CLIENT_8", "CLIENT_9", "CLIENT_2"};
	Data dataEntradaTest[NPROVES] =
	{
		{ 2, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 12, 2018 },
		{ 2, 1, 2018 },
		{ 1, 6, 2018 },
		{ 1, 6, 2018 },
		{ 1, 6, 2018 },
	};
	Data dataSortidaTest[NPROVES] = 
	{
		{ 3, 1, 2018 },
		{ 3, 1, 2018 },
		{ 3, 12, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 }
	};
	int nHabitacionsTest[NPROVES] = { 1, 2, 6, 0, 0, 0, 0 };
	float preuTest[NPROVES] = {100.0, 400.0, 1200.0, 0, 0, 0, 0};
	bool validTest[NPROVES] = { true, true, false, false, false, false, false };


	for (int p = 0; p < NPROVES; p++)
	{
		json outputTest =
		{
			{"name", "TEST CONSULTA RESERVA " + to_string(p + 1)},
			{"visibility", "visible"},
			{"output", ""}
		};

		outputParcial << "TEST CONSULTA RESERVA " << p + 1 << endl;
		outputParcial << "------------------------" << endl;

		outputParcial << "Nom Client: " << nomTest[p] << endl;
		outputParcial << "Data Entrada: " << dataEntradaTest[p].getDia() << "/" << dataEntradaTest[p].getMes() << "/" << dataEntradaTest[p].getAny() << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTest[p], outputParcial); outputParcial << endl;
		if (validTest[p])
		{
			outputParcial << "Data sortida esperada: " << dataSortidaTest[p].getDia() << "/" << dataSortidaTest[p].getMes() << "/" << dataSortidaTest[p].getAny() << endl;
			outputParcial << "Num. habitacions esperat: " << nHabitacionsTest[p] << endl;
			outputParcial << "Preu esperat: " << preuTest[p] << endl;
		}
		outputParcial << "------" << endl;
		Data dataSortida;
		int nHabitacions;
		float preu;
		bool valid = reserves.consultaReserva(nomTest[p], dataEntradaTest[p], dataSortida, nHabitacions, preu);
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		if (valid)
		{
			outputParcial << "Data sortida obtingutda: " << dataSortida.getDia() << "/" << dataSortida.getMes() << "/" << dataSortida.getAny() << endl;
			outputParcial << "Num. habitacions obtingut: " << nHabitacions << endl;
			outputParcial << "Preu obtingut: " << preu << endl;
		}
		outputParcial << "------" << endl;
		if (valid == validTest[p])
		{
			if (valid)
				if ((dataSortida == dataSortidaTest[p]) && (nHabitacions == nHabitacionsTest[p]) &&
					(fabs(preu - preuTest[p]) < 0.1))
				{
					outputParcial << "CORRECTE" << endl;
					outputTest["status"] = "passed";
					grade += 0.3;
				}
				else
				{
					outputParcial << "ERROR" << endl;
					outputTest["status"] = "failed";
				}
			else
			{
				outputParcial << "CORRECTE" << endl;
				outputTest["status"] = "passed";
				grade += 0.3;
			}
		}
		else
		{
			outputParcial << "ERROR" << endl;
			outputTest["status"] = "failed";
		}
		outputParcial << "-----------------------------------------------" << endl;
		cout << outputParcial.str();
		outputTest["output"] = outputParcial.str();
		outputParcial.str("");

		output["score"] = grade;
		output["tests"].push_back(outputTest);
		jsonFile.open("results.json");
		jsonFile << setw(4) << output << endl;
		jsonFile.close();
		cout << endl << "Grade :=>> " << grade << endl << endl;
	}
}

void testConstructorCopia(ReservesHotel& reserves, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	json outputTest =
	{
		{"name", "TEST CONSTRUCTOR COPIA"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST CONSTRUCTOR COPIA" << endl;
	outputParcial << "----------------------" << endl;


	outputParcial << endl <<  "Inicialitzant nou objecte ReservesHotel amb constructor de copia....." << endl;
	outputParcial << "------" << endl;

	ReservesHotel copia(reserves);

	outputParcial << endl << "Executant test metode CONSULTARESERVA a l'objecte inicialitzat amb la copia....." << endl;
	outputParcial << "------" << endl;

	const int NPROVES = 7;

	string nomTest[NPROVES] = { "CLIENT_2", "client_a", "CLIENT_7", "client_b", "CLIENT_8", "CLIENT_9", "CLIENT_2" };
	Data dataEntradaTest[NPROVES] =
	{
		{ 2, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 12, 2018 },
		{ 2, 1, 2018 },
		{ 1, 6, 2018 },
		{ 1, 6, 2018 },
		{ 1, 6, 2018 },
	};
	Data dataSortidaTest[NPROVES] =
	{
		{ 3, 1, 2018 },
		{ 3, 1, 2018 },
		{ 3, 12, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 }
	};
	int nHabitacionsTest[NPROVES] = { 1, 2, 6, 0, 0, 0, 0 };
	float preuTest[NPROVES] = { 100.0, 400.0, 1200.0, 0, 0, 0, 0 };
	bool validTest[NPROVES] = { true, true, false, false, false, false, false };

	bool correcte = true;
	for (int p = 0; p < NPROVES; p++)
	{
		outputParcial << "TEST CONSULTA RESERVA " << p + 1 << endl;
		outputParcial << "------------------------" << endl;

		outputParcial << "Nom Client: " << nomTest[p] << endl;
		outputParcial << "Data Entrada: " << dataEntradaTest[p].getDia() << "/" << dataEntradaTest[p].getMes() << "/" << dataEntradaTest[p].getAny() << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTest[p], outputParcial); outputParcial << endl;
		if (validTest[p])
		{
			outputParcial << "Data sortida esperada: " << dataSortidaTest[p].getDia() << "/" << dataSortidaTest[p].getMes() << "/" << dataSortidaTest[p].getAny() << endl;
			outputParcial << "Num. habitacions esperat: " << nHabitacionsTest[p] << endl;
			outputParcial << "Preu esperat: " << preuTest[p] << endl;
		}
		outputParcial << "------" << endl;
		Data dataSortida;
		int nHabitacions;
		float preu;
		bool valid = copia.consultaReserva(nomTest[p], dataEntradaTest[p], dataSortida, nHabitacions, preu);
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		if (valid)
		{
			outputParcial << "Data sortida obtingutda: " << dataSortida.getDia() << "/" << dataSortida.getMes() << "/" << dataSortida.getAny() << endl;
			outputParcial << "Num. habitacions obtingut: " << nHabitacions << endl;
			outputParcial << "Preu obtingut: " << preu << endl;
		}
		outputParcial << "------" << endl;
		if (valid == validTest[p])
		{
			if (valid)
				if ((dataSortida == dataSortidaTest[p]) && (nHabitacions == nHabitacionsTest[p]) &&
					(fabs(preu - preuTest[p]) < 0.1))
				{
					outputParcial << "CORRECTE" << endl;
				}
				else
				{
					outputParcial << "ERROR" << endl;
					correcte = false;
				}
			else
			{
				outputParcial << "CORRECTE" << endl;
			}
		}
		else
		{
			outputParcial << "ERROR" << endl;
			correcte = false;
		}
		outputParcial << "-----------------------------------------------" << endl;
	}
	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	if (correcte)
	{
		grade += 2.5;
		outputTest["status"] = "passed";
	}
	else
		outputTest["status"] = "failed";

	output["score"] = grade;
	output["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	cout << endl << "Grade :=>> " << grade << endl << endl;
}

void testOperadorAssignacio(ReservesHotel& reserves, json& output)
{
	stringstream outputParcial;
	ofstream jsonFile;
	float grade = output["score"];

	json outputTest =
	{
		{"name", "TEST OPERADOR ASSIGNACIO"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "TEST OPERADOR ASSIGNACIO" << endl;
	outputParcial << "------------------------" << endl;

	outputParcial << endl << "Inicialitzant nou objecte ReservesHotel amb operador assignacio....." << endl;
	outputParcial << "------" << endl;

	ReservesHotel assignacio;

	assignacio = reserves;

	outputParcial << endl << "Executant test metode CONSULTARESERVA a l'objecte inicialitzat amb operador assignacio....." << endl;
	outputParcial << "------" << endl;

	const int NPROVES = 7;

	string nomTest[NPROVES] = { "CLIENT_2", "client_a", "CLIENT_7", "client_b", "CLIENT_8", "CLIENT_9", "CLIENT_2" };
	Data dataEntradaTest[NPROVES] =
	{
		{ 2, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 12, 2018 },
		{ 2, 1, 2018 },
		{ 1, 6, 2018 },
		{ 1, 6, 2018 },
		{ 1, 6, 2018 },
	};
	Data dataSortidaTest[NPROVES] =
	{
		{ 3, 1, 2018 },
		{ 3, 1, 2018 },
		{ 3, 12, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 1, 2018 }
	};
	int nHabitacionsTest[NPROVES] = { 1, 2, 6, 0, 0, 0, 0 };
	float preuTest[NPROVES] = { 100.0, 400.0, 1200.0, 0, 0, 0, 0 };
	bool validTest[NPROVES] = { true, true, false, false, false, false, false };

	bool correcte = true;
	for (int p = 0; p < NPROVES; p++)
	{
		outputParcial << "TEST CONSULTA RESERVA " << p + 1 << endl;
		outputParcial << "------------------------" << endl;

		outputParcial << "Nom Client: " << nomTest[p] << endl;
		outputParcial << "Data Entrada: " << dataEntradaTest[p].getDia() << "/" << dataEntradaTest[p].getMes() << "/" << dataEntradaTest[p].getAny() << endl;
		outputParcial << "------" << endl;
		outputParcial << "Valor retorn esperat: "; mostraBool(validTest[p], outputParcial); outputParcial << endl;
		if (validTest[p])
		{
			outputParcial << "Data sortida esperada: " << dataSortidaTest[p].getDia() << "/" << dataSortidaTest[p].getMes() << "/" << dataSortidaTest[p].getAny() << endl;
			outputParcial << "Num. habitacions esperat: " << nHabitacionsTest[p] << endl;
			outputParcial << "Preu esperat: " << preuTest[p] << endl;
		}
		outputParcial << "------" << endl;
		Data dataSortida;
		int nHabitacions;
		float preu;
		bool valid = assignacio.consultaReserva(nomTest[p], dataEntradaTest[p], dataSortida, nHabitacions, preu);
		outputParcial << "Valor retorn obtingut: "; mostraBool(valid, outputParcial); outputParcial << endl;
		if (valid)
		{
			outputParcial << "Data sortida obtingutda: " << dataSortida.getDia() << "/" << dataSortida.getMes() << "/" << dataSortida.getAny() << endl;
			outputParcial << "Num. habitacions obtingut: " << nHabitacions << endl;
			outputParcial << "Preu obtingut: " << preu << endl;
		}
		outputParcial << "------" << endl;
		if (valid == validTest[p])
		{
			if (valid)
				if ((dataSortida == dataSortidaTest[p]) && (nHabitacions == nHabitacionsTest[p]) &&
					(fabs(preu - preuTest[p]) < 0.1))
				{
					outputParcial << "CORRECTE" << endl;
				}
				else
				{
					outputParcial << "ERROR" << endl;
					correcte = false;
				}
			else
			{
				outputParcial << "CORRECTE" << endl;
			}
		}
		else
		{
			outputParcial << "ERROR" << endl;
			correcte = false;
		}
		outputParcial << "-----------------------------------------------" << endl;
	}
	cout << outputParcial.str();
	outputTest["output"] = outputParcial.str();
	outputParcial.str("");

	if (correcte)
	{
		grade += 2.5;
		outputTest["status"] = "passed";
	}
	else
		outputTest["status"] = "failed";

	output["score"] = grade;
	output["tests"].push_back(outputTest);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();
	cout << endl << "Grade :=>> " << grade << endl << endl;
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


	json outputTest1 =
	{
		{"name", "INICIALITZACIO TEST 1"},
		{"visibility", "visible"},
		{"output", ""}
	};
	
	stringstream outputParcial;

	outputParcial << "INICIALITZACIO DEL TEST 1" << endl;
	outputParcial << "-------------------------" << endl;
	outputParcial << "Cridant al constructor de ReservesHotel per inicialitzar dades de l'hotel....." << endl;
	ReservesHotel reserves("hotel_1", 100.0, 10, 9);
	outputParcial << "---------" << endl;
	outputParcial << "Nom de l'hotel: hotel_1" << endl;
	outputParcial << "Preu per dia: 100.0" << endl;
	outputParcial << "Num. habitacions: 10" << endl;
	outputParcial << "---------" << endl;
	outputParcial << "Llegint reserves del fitxer 'reserves1.txt'....." << endl;
	reserves.llegeixReserves("reserves1.txt");	
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputTest1["output"] = outputParcial.str();
	outputParcial.str("");

	output["tests"].push_back(outputTest1);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();


	testNReservesDia(reserves, output);
	testAfegeixReserva(reserves, output);

	json outputTest2 =
	{
		{"name", "INICIALITZACIO TEST 2"},
		{"visibility", "visible"},
		{"output", ""}
	};

	outputParcial << "INICIALITZACIO DEL TEST 2" << endl;
	outputParcial << "-------------------------" << endl;
	outputParcial << "Llegint reserves del fitxer 'reserves2.txt'....." << endl;
	reserves.llegeixReserves("reserves2.txt");
	outputParcial << "-----------------------------------------------" << endl;
	cout << outputParcial.str();
	outputTest2["output"] = outputParcial.str();
	outputParcial.str("");

	output["tests"].push_back(outputTest2);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	testConsultaReserva(reserves, output);
	testConstructorCopia(reserves, output);
	testOperadorAssignacio(reserves, output);

	grade = output["score"];
	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}