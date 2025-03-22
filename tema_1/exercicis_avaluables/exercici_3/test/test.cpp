#include "../source/gestio_aules.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;




void mostraBool(bool valor, stringstream& outputParcial)
{
	if (valor)
		outputParcial << "TRUE ";
	else
		outputParcial << "FALSE ";
}

void mostraArrayString(string arrayString[], int nElements, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < (nElements - 1); i++)
		outputParcial << arrayString[i] << ", ";
	if (nElements > 0)
		outputParcial << arrayString[nElements - 1];
	outputParcial << "]" << endl;
}

bool pertanyElement(const string& element, string array[], int nElements)
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

bool igualArrayString(string array1[], int nElements1, string array2[], int nElements2)
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

void mostraFitxer(string fitxer[], int nLinies, stringstream& outputParcial)
{
	for (int i = 0; i < nLinies; i++)
	{
		outputParcial << fitxer[i] << endl;
	}
}

void llegeixFitxer(const string& nomFitxer, string fitxer[], int& nLinies)
{
	ifstream fitxerIn(nomFitxer);
	if (fitxerIn.is_open())
	{
		nLinies = 0;
		while (!fitxerIn.eof())
		{
			getline(fitxerIn, fitxer[nLinies]);
			if (fitxer[nLinies] != "")
				nLinies++;
		}
		fitxerIn.close();
	}
}

bool igualLinia(const string& linia, string fitxer[], int nLinies)
{
	int i = 0;
	bool igual = (linia == "");
	while ((i < nLinies) && !igual)
	{
		if (linia == fitxer[i])
			igual = true;
		else
			i++;
	}
	return igual;
}

bool igualFitxer(string fitxer1[], int nLinies1, string fitxer2[], int nLinies2)
{
	bool iguals = true;
	int i = 0;
	while ((i < nLinies1) && iguals)
	{
		if (!igualLinia(fitxer1[i], fitxer2, nLinies2))
			iguals = false;
		else
			i++;
	}
	i = 0;
	while ((i < nLinies2) && iguals)
	{
		if (!igualLinia(fitxer2[i], fitxer1, nLinies1))
			iguals = false;
		else
			i++;
	}
	return iguals;
}

void afegeixAssignatures(GestioAules& ga, string& outputFinal)
{
	const int N_PROVES = 5;
	string codi[N_PROVES] = { "ASSIG_1", "ASSIG_2", "ASSIG_3", "ASSIG_4", "ASSIG_5" };
	int nMatriculats[N_PROVES] = { 30, 50, 50, 50, 50 };
	string dia[N_PROVES] = { "DILLUNS", "DILLUNS", "DILLUNS", "DILLUNS", "DIMARTS" };
	int horaInici[N_PROVES] = { 10, 10, 11, 10, 10 };
	int horaFi[N_PROVES] = { 12, 12, 13, 12, 12 };
	int setmanaInici[N_PROVES] = { 1, 1, 2, 1, 1 };
	int setmanaFinal[N_PROVES] = { 10, 10, 10, 15, 15 };

	stringstream outputParcial;

	outputParcial << "Llegim les assignatures seguents del fitxer assignatures.txt amb el metode inicialitzaAssignatures" << endl;
	outputParcial << "----------" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "Codi: " << codi[i] << endl;
		outputParcial << "N. matriculats: " << nMatriculats[i] << endl;
		outputParcial << "Dia: " << dia[i] << endl;
		outputParcial << "Hora inici: " << horaInici[i] << endl;
		outputParcial << "Hora fi: " << horaFi[i] << endl;
		outputParcial << "Setmana inici: " << setmanaInici[i] << endl;
		outputParcial << "Setmana final: " << setmanaFinal[i] << endl;
		outputParcial << "----------" << endl;
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	ga.inicialitzaAssignatures("assignatures.txt");
}

void afegeixAules(GestioAules& ga, string& outputFinal)
{
	const int N_PROVES = 4;
	const int MAX_RESERVES = 3;
	string codi[N_PROVES] = { "AULA_1", "AULA_2", "AULA_3", "AULA_4" };
	int capacitat[N_PROVES] = { 120, 60, 40, 100 };
	int nReserves[N_PROVES] = { 0, 1, 3, 0 };
	string dia[N_PROVES][MAX_RESERVES] = 
	{
		{},
		{ "DIMARTS" },
		{ "DILLUNS", "DIJOUS", "DIVENDRES" },
		{}
	};
	int horaInici[N_PROVES][MAX_RESERVES] = 
	{
		{},
		{ 10 },
		{ 11, 10, 11 },
		{}
	};
	int horaFi[N_PROVES][MAX_RESERVES] = 
	{
		{},
		{ 12 },
		{ 13, 12, 13 },
		{}
	};
	int setmanaInici[N_PROVES][MAX_RESERVES] = 
	{
		{},
		{ 1 },
		{ 2, 1, 1 },
		{}
	};
	int setmanaFinal[N_PROVES][MAX_RESERVES] = 
	{
		{},
		{ 15 },
		{ 8, 15, 15 },
		{}
	};

	stringstream outputParcial;

	outputParcial << "Llegim les aules seguents del fitxer aules.txt amb el metode inicialitzaAules" << endl;
	outputParcial << "----------" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "Codi: " << codi[i] << endl;
		outputParcial << "Capacitat: " << capacitat[i] << endl;
		for (int j = 0; j < nReserves[i]; j++)
		{
			outputParcial << "---" << endl;
			outputParcial << "Reserva " << j + 1 << endl;
			outputParcial << "Dia: " << dia[i][j] << endl;
			outputParcial << "Hora inici: " << horaInici[i][j] << endl;
			outputParcial << "Hora fi: " << horaFi[i][j] << endl;
			outputParcial << "Setmana inici: " << setmanaInici[i][j] << endl;
			outputParcial << "Setmana final: " << setmanaFinal[i][j] << endl;
		}
		outputParcial << "----------" << endl;
	}
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	ga.inicialitzaAules("aules.txt");
}


float testReservesAula1(GestioAules& ga, json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST RESERVES AULA 1"},
		{"visibility", "visible"},
		{"output", ""}
	};

	const int MAX_LINIES = 10;
	string fitxerEsperat[MAX_LINIES] = 
	{
		"DILLUNS 11 13 2 8",
		"DIJOUS 10 12 1 15",
		"DIVENDRES 11 13 1 15",
	};
	int nLiniesEsperades = 3;	
	string fitxerObtingut[MAX_LINIES];
	int nLiniesObtingudes = 0;


	outputParcial << endl << endl;
	outputParcial << "Iniciant test metode reservesAula" << endl;
	outputParcial << "=================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	
	outputParcial << endl;
	outputParcial << "Reserves de l'aula AULA_3" << endl;
	outputParcial << "------------------------" << endl;
	outputParcial << "Contingut esperat del fitxer: " << endl;
	mostraFitxer(fitxerEsperat, nLiniesEsperades, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Escrivint reserves al fitxer reserves_aula_3.txt" << endl;
	const string nomFitxerSortida = "reserves_aula_3.txt";
	ga.reservesAula("AULA_3", nomFitxerSortida);
	outputParcial << "----------" << endl;
	llegeixFitxer(nomFitxerSortida, fitxerObtingut, nLiniesObtingudes);
	outputParcial << "Contingut obtingut del fitxer: " << endl;
	mostraFitxer(fitxerObtingut, nLiniesObtingudes, outputParcial);
	outputParcial << "----------" << endl;

	if (igualFitxer(fitxerEsperat, nLiniesEsperades, fitxerObtingut, nLiniesObtingudes))
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 1.0;
	}
	outputParcial << "-----------------------------------------------" << endl;
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


float testAssignaAula(GestioAules& ga, json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	ofstream jsonFile;
	const int N_PROVES = 5;
	string codiAssignatura[N_PROVES] = { "ASSIG_1", "ASSIG_2", "ASSIG_3", "ASSIG_4", "ASSIG_5" };
	string aulaEsperada[N_PROVES] = { "AULA_2", "AULA_4", "AULA_1", "", "AULA_4" };

	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
        stringstream outputParcial;

        outputTest =
        {
            {"name", "TEST ASSIGNA AULA " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

		outputParcial << endl << endl;
		outputParcial << "TEST ASSIGNA AULA " << i + 1 << endl;
		outputParcial << "====================" << endl;
		outputParcial << "Codi assignatura: " << codiAssignatura[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Codi aula esperada: " << aulaEsperada[i] << endl;
		outputParcial << "----------" << endl;
		string aulaObtinguda = ga.assignaAula(codiAssignatura[i]);
		outputParcial << "Codi aula obtinguda: " << aulaObtinguda << endl;
		outputParcial << "----------" << endl;
		bool correcte = (aulaEsperada[i] == aulaObtinguda);
		if (correcte)
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "-----------------------------------------------" << endl;

        cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

        if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 0.5;
        }		    
	    else
		    outputTest["status"] = "failed";

        outputGeneral["score"] = grade;
        outputGeneral["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << outputGeneral << endl;
        jsonFile.close();
	}


	if (reduccio > 5.0)
		reduccio = 5.0;

	return reduccio;
}


float testEliminaReserva(GestioAules& ga, json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	ofstream jsonFile;
	const int N_PROVES = 2;
	string codiAssignatura[N_PROVES] = { "ASSIG_4",  "ASSIG_1" };
	bool resultatEsperat[N_PROVES] = { false, true };
	string codiAssignar = "ASSIG_4";
	string aulaEsperada = "AULA_2";

	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
        stringstream outputParcial;

        outputTest =
        {
            {"name", "TEST ELIMINA RESERVA " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

		outputParcial << endl << endl;
		outputParcial << "TEST ELIMINA RESERVA " << i + 1 << endl;
		outputParcial << "========================" << endl;
		outputParcial << "Codi assignatura: " << codiAssignatura[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Resultat esperat: "; 
		mostraBool(resultatEsperat[i], outputParcial);
		outputParcial << endl;
		outputParcial << "----------" << endl;
		bool resultat = ga.eliminaReserva(codiAssignatura[i]);
		outputParcial << "Resultat obtingut: ";
		mostraBool(resultat, outputParcial); 
		outputParcial << endl;
		outputParcial << "----------" << endl;
		bool correcte = (resultatEsperat[i] == resultat);
		if (resultatEsperat[i])
		{
			outputParcial << "Intentem ara assignar una assignatura a l'aula alliberada" << endl;
			outputParcial << "----------" << endl;
			outputParcial << "Codi assignatura: " << codiAssignar << endl;
			outputParcial << "----------" << endl;
			outputParcial << "Codi aula esperada: " << aulaEsperada << endl;
			outputParcial << "----------" << endl;
			string aulaObtinguda = ga.assignaAula(codiAssignar);
			outputParcial << "Codi aula assignada: " << aulaObtinguda << endl;
			outputParcial << "----------" << endl;
			correcte = correcte && (aulaEsperada == aulaObtinguda);
		}
		if (correcte)
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "-----------------------------------------------" << endl;

        cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

        if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 0.5;
        }		    
	    else
		    outputTest["status"] = "failed";

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


float testAssignaturesAula(GestioAules& ga, json& outputGeneral)
{
	float reduccio = 0.0;
	float grade = 0.0;

	ofstream jsonFile;
	const int N_PROVES = 4;
	const int MAX_ASSIGNATURES = 5;
	string codiAula[N_PROVES] = { "AULA_1", "AULA_2", "AULA_3", "AULA_4" };
	int nAssignaturesEsperades[N_PROVES] = { 1, 1, 0, 2 };
	string assignaturesEsperades[N_PROVES][MAX_ASSIGNATURES] =
	{
		{ "ASSIG_3" },
		{ "ASSIG_4" },
		{},
		{ "ASSIG_2", "ASSIG_5" }
	};

	for (int i = 0; i < N_PROVES; i++)
	{
		json outputTest;
        stringstream outputParcial;

        outputTest =
        {
            {"name", "TEST ASSIGNATURES AULA " + to_string(i + 1)},
            {"visibility", "visible"},
            {"output", ""}
        };

		outputParcial << endl << endl;
		outputParcial << "TEST ASSIGNATURES AULA " << i + 1 << endl;
		outputParcial << "=========================" << endl;
		outputParcial << "Codi aula: " << codiAula[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "N. assignatures esperades: " << nAssignaturesEsperades[i] << endl;
		outputParcial << "Assignatures esperades: ";
		mostraArrayString(assignaturesEsperades[i], nAssignaturesEsperades[i], outputParcial);
		outputParcial << "----------" << endl;
		int nAssignaturesObtingudes;
		string assignaturesObtingudes[MAX_ASSIGNATURES];
		ga.assignaturesAula(codiAula[i], nAssignaturesObtingudes, assignaturesObtingudes);
		outputParcial << "N. assignatures obtingudes: " << nAssignaturesObtingudes << endl;
		outputParcial << "Assignatures obtingudes: ";
		mostraArrayString(assignaturesObtingudes, nAssignaturesObtingudes, outputParcial);
		outputParcial << "----------" << endl;
		bool correcte = igualArrayString(assignaturesEsperades[i], nAssignaturesEsperades[i], assignaturesObtingudes, nAssignaturesObtingudes);
		if (correcte)
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 0.5;
		}
		outputParcial << "-----------------------------------------------" << endl;

        cout << outputParcial.str();
        outputTest["output"] = outputParcial.str();
        outputParcial.str("");

        if (correcte)
        {
            outputTest["status"] = "passed";
            grade += 0.25;
        }		    
	    else
		    outputTest["status"] = "failed";

        outputGeneral["score"] = grade;
        outputGeneral["tests"].push_back(outputTest);
        jsonFile.open("results.json");
        jsonFile << setw(4) << outputGeneral << endl;
        jsonFile.close();
	}


	if (reduccio > 1.0)
		reduccio = 1.0;

	return reduccio;
}

float testReservesAula2(GestioAules& ga, json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST RESERVES AULA 2"},
		{"visibility", "visible"},
		{"output", ""}
	};

	const int MAX_LINIES = 10;
	string fitxerEsperat[MAX_LINIES] = 
	{
		"DIMARTS 10 12 1 15",
		"DILLUNS 10 12 1 15",
	};
	int nLiniesEsperades = 2;	
	string fitxerObtingut[MAX_LINIES];
	int nLiniesObtingudes = 0;


	outputParcial << endl << endl;
	outputParcial << "Iniciant test metode reservesAula" << endl;
	outputParcial << "=================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	
	outputParcial << endl;
	outputParcial << "Reserves de l'aula AULA_2" << endl;
	outputParcial << "------------------------" << endl;
	outputParcial << "Contingut esperat del fitxer: " << endl;
	mostraFitxer(fitxerEsperat, nLiniesEsperades, outputParcial);
	outputParcial << "----------" << endl;
	outputParcial << "Escrivint reserves al fitxer reserves_aula_2.txt" << endl;
	const string nomFitxerSortida = "reserves_aula_2.txt";
	ga.reservesAula("AULA_2", nomFitxerSortida);
	outputParcial << "----------" << endl;
	llegeixFitxer(nomFitxerSortida, fitxerObtingut, nLiniesObtingudes);
	outputParcial << "Contingut obtingut del fitxer: " << endl;
	mostraFitxer(fitxerObtingut, nLiniesObtingudes, outputParcial);
	outputParcial << "----------" << endl;

	if (igualFitxer(fitxerEsperat, nLiniesEsperades, fitxerObtingut, nLiniesObtingudes))
		outputParcial << "CORRECTE" << endl;
	else
	{
		outputParcial << "ERROR" << endl;
		reduccio += 1.0;
	}
	outputParcial << "-----------------------------------------------" << endl;
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

	json output;
	ofstream jsonFile;

	output["score"] = grade;
	output["visibility"] = "visible";
	output["stdout_visibility"] = "visible";
	output["tests"] = json::array();

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	string outputGeneral;

	GestioAules ga;
    
	afegeixAssignatures(ga, outputGeneral);
	output["output"] = outputGeneral;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	afegeixAules(ga, outputGeneral);
	output["output"] = outputGeneral;
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestReservesAula1;
	float reduccio = testReservesAula1(ga, outputTestReservesAula1);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestReservesAula1);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	reduccio = testAssignaAula(ga, output);
    grade = grade + (5 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	reduccio = testEliminaReserva(ga, output);
    grade = grade + (2 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	reduccio = testAssignaturesAula(ga, output);
    grade = grade + (1 - reduccio);         
	cout << "Grade :=>> " << grade << endl;
    output["score"] = grade;
    jsonFile.open("results.json");
    jsonFile << setw(4) << output << endl;
    jsonFile.close();

	json outputTestReservesAula2;
	reduccio = testReservesAula2(ga, outputTestReservesAula2);
	grade = grade + (1 - reduccio);
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestReservesAula2);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}



