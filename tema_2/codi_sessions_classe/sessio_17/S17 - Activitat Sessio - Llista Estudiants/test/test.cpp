#include "../source/titulacio.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void mostraBool(bool logic, stringstream& outputParcial)
{
	if (logic)
		outputParcial << "TRUE";
	else
		outputParcial << "FALSE";
}

void mostraLlista(NodeEstudiant* primer, stringstream& outputParcial)
{
	NodeEstudiant* aux = primer;
	outputParcial << "[";
	while (aux != nullptr)
	{
		Estudiant e = aux->getValor();
		outputParcial << e.getNiu() << " ";
		aux = aux->getNext();
	}
	outputParcial << "]" << endl;
}

void mostraArray(Estudiant *array, int nElements, stringstream& outputParcial)
{
	outputParcial << "[";
	for (int i = 0; i < nElements; i++)
	{
		outputParcial << array[i].getNiu() << " ";
	}
	outputParcial << "]" << endl;
}

bool igualsArrayLlista(NodeEstudiant* primer, Estudiant* array, int nElements)
{
	bool iguals = true;
	int i = 0;
	NodeEstudiant* aux = primer;
	while (iguals && (i < nElements) && (aux != nullptr))
	{
		if (aux->getValor().getNiu() != array[i].getNiu())
			iguals = false;
		else
		{
			i++;
			aux = aux->getNext();
		}
	}
	iguals = iguals && (i == nElements) && (aux == nullptr);
	return iguals;
}

float testConsulta(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST CONSULTA ESTUDIANT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	Titulacio t;

	const int N_PROVES = 4;
	const int N_ESTUDIANTS = 4;
	Estudiant valorsAfegits[N_ESTUDIANTS] =
	{
		{ "niu_1", "nom_1" },
		{ "niu_2", "nom_2" },
		{ "niu_3", "nom_3" },
		{ "niu_4", "nom_4" }
	};
	string valorsConsultats[N_PROVES] = { "niu_2", "niu_4", "niu_1", "niu_5"};

	Estudiant valorEsperat[N_PROVES] =
	{
		{ "niu_2", "nom_2" },
		{ "niu_4", "nom_4" },
		{ "niu_1", "nom_1" },
		{ "", "" }
	};
	bool valorRetornEsperat[N_PROVES] = { true, true, true, false };
	int nElementsEsperat[N_PROVES] = { 3, 2, 1, 1};
	outputParcial << "TEST CONSULTA ESTUDIANT" << endl;
	outputParcial << "-----------------------" << endl;
	outputParcial << "Afegint els seguents estudiants amb el metode insereix" << endl;
	for (int i = 0; i < N_ESTUDIANTS; i++)
	{
		outputParcial << valorsAfegits[i].getNiu() << ", " << valorsAfegits[i].getNom() << endl;
		t.insereixEstudiant(valorsAfegits[i].getNiu(), valorsAfegits[i].getNom());
	}
	outputParcial << "------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "--------" << endl;
		outputParcial << "Consultem l'estudiant: " << valorsConsultats[i] << endl;
		Estudiant e;
		bool trobat = t.consultaEstudiant(valorsConsultats[i], e);
		outputParcial << "--------" << endl;
		outputParcial << "Valor de retorn esperat: "; mostraBool(valorRetornEsperat[i], outputParcial); outputParcial << endl;
		if (valorRetornEsperat[i])
			outputParcial << "Valor esperat de l'estudiant: " << valorEsperat[i].getNiu() << ", " << valorEsperat[i].getNom() << endl;
		outputParcial << "---------" << endl;
		outputParcial << "Valor de retorn obtingut: "; mostraBool(trobat, outputParcial); outputParcial << endl;
		if (trobat)
			outputParcial << "Valor obtingut de l'estudiant: " << e.getNiu() << ", " << e.getNom() << endl;
		outputParcial << "---------" << endl;
		if (trobat == valorRetornEsperat[i])
			if (trobat)
				if ((e.getNiu() != valorEsperat[i].getNiu()) || (e.getNom() != valorEsperat[i].getNom()))
				{
					outputParcial << "ERROR" << endl;
					reduccio += 1.0;
				}
				else
					outputParcial << "CORRECTE" << endl;
			else
				outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		outputParcial << "-----------------------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";
	if (reduccio > 2.0)
		reduccio = 2.0;
	return reduccio;
}


float testElimina(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST ELIMINA ESTUDIANT"},
		{"visibility", "visible"},
		{"output", ""}
	};
	Titulacio t;

	const int N_PROVES = 5;
	const int N_ESTUDIANTS = 4;
	Estudiant valorsAfegits[N_ESTUDIANTS] =
	{
		{ "niu_1", "nom_1" },
		{ "niu_2", "nom_2" },
		{ "niu_3", "nom_3" },
		{ "niu_4", "nom_4" }
	};
	string valorsEliminats[N_PROVES] = { "niu_2", "niu_4", "niu_1", "niu_1", "niu_3" };

	Estudiant valorEsperat[N_PROVES][N_ESTUDIANTS] =
	{
		{
			{ "niu_1", "nom_1" },
			{ "niu_3", "nom_3" },
			{ "niu_4", "nom_4" }
		},
		{
			{ "niu_1", "nom_1" },
			{ "niu_3", "nom_3" }
		},
		{
			{ "niu_3", "nom_3" }
		},
		{
			{ "niu_3", "nom_3" }
		},
		{
			{}
		}
	};
	
	int nElementsEsperat[N_PROVES] = { 3, 2, 1, 1, 0 };
	outputParcial << "TEST ELIMINA ESTUDIANT" << endl;
	outputParcial << "----------------------" << endl;
	outputParcial << "Afegint els seguents estudiants amb el metode insereix" << endl;
	for (int i = 0; i < N_ESTUDIANTS; i++)
	{
		outputParcial << valorsAfegits[i].getNiu() << ", " << valorsAfegits[i].getNom() << endl;
		t.insereixEstudiant(valorsAfegits[i].getNiu(), valorsAfegits[i].getNom());
	}
	outputParcial << "-----------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");
	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "--------" << endl;
		outputParcial << "Eliminem l'estudiant: " << valorsEliminats[i] << endl;
		t.eliminaEstudiant(valorsEliminats[i]);
		outputParcial << "--------" << endl;
		outputParcial << "Valor esperat de la llista d'estudiants: " << endl;
		mostraArray(valorEsperat[i], nElementsEsperat[i], outputParcial);
		outputParcial << "---------" << endl;
		outputParcial << "Valor obtingut de la llista d'estudiants: " << endl;
		mostraLlista(t.getPrimerEstudiant(), outputParcial);
		outputParcial << "--------" << endl;
		if (!igualsArrayLlista(t.getPrimerEstudiant(), valorEsperat[i], nElementsEsperat[i]))
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		else
			outputParcial << "CORRECTE" << endl;
		outputParcial << "--------------------------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 2.0)
		reduccio = 2.0;
	return reduccio;
}


float testInsereix(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST INSEREIX ESTUDIANT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	Titulacio t;

	const int N_ESTUDIANTS = 4;
	Estudiant valorsAfegits[N_ESTUDIANTS] =
	{
		{ "niu_3", "nom_3" },
		{ "niu_1", "nom_1" },
		{ "niu_2", "nom_2" },
		{ "niu_4", "nom_4" }
	};
	Estudiant valorsEsperats[N_ESTUDIANTS] =
	{
		{ "niu_1", "nom_1" },
		{ "niu_2", "nom_2" },
		{ "niu_3", "nom_3" },
		{ "niu_4", "nom_4" }
	};
	outputParcial << "TEST INSEREIX ESTUDIANT" << endl;
	outputParcial << "-----------------------" << endl;
	outputParcial << "Afegint els seguents estudiants ordenats amb el metode insereix" << endl;
	for (int i = 0; i < N_ESTUDIANTS; i++)
	{
		outputParcial << valorsAfegits[i].getNiu() << ", " << valorsAfegits[i].getNom() << endl;
		t.insereixEstudiant(valorsAfegits[i].getNiu(), valorsAfegits[i].getNom());
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	outputParcial << "-----------------------" << endl;
	outputParcial << "Valor esperat de la llista d'estudiants: " << endl;
	mostraArray(valorsEsperats, N_ESTUDIANTS, outputParcial);
	outputParcial << "---------" << endl;
	outputParcial << "Valor obtingut de la llista d'estudiants: " << endl;;
	mostraLlista(t.getPrimerEstudiant(), outputParcial);
	outputParcial << "--------" << endl;
	if (!igualsArrayLlista(t.getPrimerEstudiant(), valorsEsperats, N_ESTUDIANTS))
	{
		outputParcial << "ERROR" << endl;
		reduccio += 2.0;
	}
	else
		outputParcial << "CORRECTE" << endl;
	outputParcial << "-----------------------------------------------" << endl;

	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 2.0)
		reduccio = 2.0;
	return reduccio;
}



float testEliminaPrimer(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST ELIMINA PRIMER ESTUDIANT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	Titulacio t;

	const int N_PROVES = 3;
	const int N_ESTUDIANTS = 2;
	Estudiant valorsAfegits[N_ESTUDIANTS] =
	{
		{ "niu_1", "nom_1" },
		{ "niu_2", "nom_2" },
	};
	Estudiant valorEsperat[N_PROVES][N_ESTUDIANTS] =
	{
		{
			{ "niu_1", "nom_1" }
		},
		{
		},
		{
		},
	};
	int nElementsEsperat[N_PROVES] = { 1, 0, 0 };
	outputParcial << "TEST ELIMINA PRIMER ESTUDIANT" << endl;
	outputParcial << "-----------------------------" << endl;
	outputParcial << "Afegint els seguents estudiants pel principi de la llista" << endl;
	for (int i = 0; i < N_ESTUDIANTS; i++)
	{
		outputParcial << "" << valorsAfegits[i].getNiu() << ", " << valorsAfegits[i].getNom() << endl;
		t.afegeixEstudiant(valorsAfegits[i].getNiu(), valorsAfegits[i].getNom());
	}
	outputParcial << "-----------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	for (int i = 0; i < N_PROVES; i++)
	{
		outputParcial << "TEST " << i + 1 << endl;
		outputParcial << "--------" << endl;
		outputParcial << "Eliminem el primer estudiant a la llista anterior" << endl;
		t.eliminaPrimerEstudiant();
		outputParcial << "--------" << endl;
		outputParcial << "Valor esperat de la llista d'estudiants: " << endl;
		mostraArray(valorEsperat[i], nElementsEsperat[i], outputParcial);
		outputParcial << "---------" << endl;
		outputParcial << "Valor obtingut de la llista d'estudiants: " << endl;
		mostraLlista(t.getPrimerEstudiant(), outputParcial);
		outputParcial << "--------" << endl;
		if (!igualsArrayLlista(t.getPrimerEstudiant(), valorEsperat[i], nElementsEsperat[i]))
		{
			outputParcial << "ERROR" << endl;
			reduccio += 1.0;
		}
		else
			outputParcial << "CORRECTE" << endl;
		outputParcial << "---------------------------------------------------" << endl;
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 2.0)
		reduccio = 2.0;
	return reduccio;
}



float testAfegeix(json& output)
{
	float reduccio = 0.0;

	stringstream outputParcial;
	string outputFinal = "";

	output =
	{
		{"name", "TEST AFEGEIX PRIMER ESTUDIANT"},
		{"visibility", "visible"},
		{"output", ""}
	};

	Titulacio t;

	const int N_PROVES = 2;
	Estudiant valorEsperat[N_PROVES] =
	{
		{ "niu_2", "nom_2" },
		{ "niu_1", "nom_1" },
	};
	outputParcial << "TEST AFEGEIX PRIMER ESTUDIANT" << endl;
	outputParcial << "-----------------------------" << endl;
	outputParcial << "Afegint els seguents estudiants pel principi de la llista" << endl;
	for (int i = N_PROVES - 1; i >= 0; i--)
	{
		outputParcial << valorEsperat[i].getNiu() << ", " << valorEsperat[i].getNom() << endl;
		t.afegeixEstudiant(valorEsperat[i].getNiu(), valorEsperat[i].getNom());
		cout << outputParcial.str();
		outputFinal += outputParcial.str();
		outputParcial.str("");
	}
	outputParcial << "------------------------------" << endl;
	outputParcial << "Valor esperat de la llista d'estudiants: " << endl;
	mostraArray(valorEsperat, N_PROVES, outputParcial);
	outputParcial << "---------" << endl;
	outputParcial << "Valor obtingut de la llista d'estudiants: " << endl;;
	mostraLlista(t.getPrimerEstudiant(), outputParcial);
	outputParcial << "---------" << endl;
	if (!igualsArrayLlista(t.getPrimerEstudiant(), valorEsperat, N_PROVES))
	{
		outputParcial << "ERROR" << endl;
		reduccio += 2.0;
	}
	else
		outputParcial << "CORRECTE" << endl;
	outputParcial << "---------------------------------------------------" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

	output["output"] = outputFinal;

	if (reduccio == 0)
		output["status"] = "passed";
	else
		output["status"] = "failed";

	if (reduccio > 2.0)
		reduccio = 2.0;
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

	cout << "Grade :=>> " << grade << endl;

	json outputTestAfegeix;
	grade += (2 - testAfegeix(outputTestAfegeix));
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestAfegeix);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestEliminaPrimer;
	grade += (2 - testEliminaPrimer(outputTestEliminaPrimer));
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestEliminaPrimer);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestInsereix;
	grade += (2 - testInsereix(outputTestInsereix));
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestInsereix);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestElimina;
	grade += (2 - testElimina(outputTestElimina));
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestElimina);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	json outputTestConsulta;
	grade += (2 - testConsulta(outputTestConsulta));
	cout << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestConsulta);
	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade < 0)
		grade = 0.0;
	if (grade >= 10.0)
	{
		grade = 10;
		cout << "Final del test sense errors" << endl;
	}

	return 0;

}