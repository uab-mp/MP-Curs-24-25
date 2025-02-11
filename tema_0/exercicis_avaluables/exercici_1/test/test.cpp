#include "..\source\cerca_substitueix.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;


float testCercaSubstitueix(json& output)
{
    float reduccio = 0.0;
    const int N_PROVES = 10;
    stringstream outputParcial;
    string outputFinal = "";

    output =
    {
        {"name", "TEST CERCA SUBSTITUEIX"},
        {"visibility", "visible"},
        {"output", ""}
    };

    string text[N_PROVES] = 
    {
        "Canviem abcd per ef",
        "Canviem abcd per efghij",
        "abcd per ab",
        "Posem efghij en el lloc de abcd",
        "Canviem abcd per ef: abcd, abcd, abc",
        "Canviem abcd per abcdef",
        "abcd, abcd, abcd, per ab, ab, ab",
        "Canviem abc per cde, i tambe abc, abc, abc",
        "abc per cdef, i tambe abc",
        "No fem cap canvi"
    };

    string stringOriginal[N_PROVES] = 
    {
        "abcd",
        "abcd",
        "abcd",
        "abcd",
        "abcd",
        "abcd",
        "abcd",
        "abc",
        "abc",
        "ac"
    };

    string stringNou[N_PROVES] = 
    {
        "ef",
        "efghij",
        "ab",
        "efghij",
        "ef",
        "abcdef",
        "ab",
        "cde",
        "cdef",
        "abc"
    };

    string textFinalEsperat[N_PROVES] = 
    {
        "Canviem ef per ef",
        "Canviem efghij per efghij",
        "ab per ab",
        "Posem efghij en el lloc de efghij",
        "Canviem ef per ef: ef, ef, abc",
        "Canviem abcdef per abcdefef",
        "ab, ab, ab, per ab, ab, ab",
        "Canviem cde per cde, i tambe cde, cde, cde",
        "cdef per cdef, i tambe cdef",
        "No fem cap canvi"
    };

    int nCanvisEsperat[N_PROVES] = { 1, 1, 1, 1, 3, 2, 3, 4, 2, 0 };
    
	outputParcial << endl << endl;
	outputParcial << "Test de la funcio cercaSubstitueix" << endl;
	outputParcial << "==================================" << endl;
	cout << outputParcial.str();
	outputFinal += outputParcial.str();
	outputParcial.str("");

    int nCanvis;
    char text_char[MAX_STRING];
    char stringOriginal_char[MAX_STRING];
    char stringNou_char[MAX_STRING];
	for (int i = 0; i < N_PROVES; i++)
	{
        outputParcial << "TEST: " << i + 1 << endl;
		outputParcial << "-------" << endl;
		outputParcial << "Text original: " << text[i] << endl;
		outputParcial << "String a substituir: " << stringOriginal[i] << endl;
		outputParcial << "Nou string: " << stringNou[i] << endl;
		outputParcial << "----------" << endl;
		outputParcial << "Text final esperat: " << textFinalEsperat[i] << endl;
		outputParcial << "N canvis esperats: " << nCanvisEsperat[i] << endl;
		outputParcial << "----------" << endl;
        strcpy(text_char, text[i].c_str());
        strcpy(stringOriginal_char, stringOriginal[i].c_str());
        strcpy(stringNou_char, stringNou[i].c_str());
        nCanvis = cercaSubstitueix(text_char, stringOriginal_char, stringNou_char);
		outputParcial << "Text final obtingut: " << text_char << endl;
		outputParcial << "N canvis obtinguts: " << nCanvis << endl;
		if ((textFinalEsperat[i] == string(text_char)) &&
			(nCanvisEsperat[i] == nCanvis))
			outputParcial << "CORRECTE" << endl;
		else
		{
			outputParcial << "ERROR" << endl;
            if ((textFinalEsperat[i] == string(text_char)) || 
                (nCanvisEsperat[i] == nCanvis))
                reduccio += 0.5;
            else
                reduccio += 1.0;
		}
		outputParcial << "--------------------------------------------------------------" << endl;
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

	json outputTestCercaSubstitueix;
	float reduccio = testCercaSubstitueix(outputTestCercaSubstitueix);
	grade = grade + (10 - reduccio);
	cout << endl << "Grade :=>> " << grade << endl;
	output["score"] = grade;
	output["tests"].push_back(outputTestCercaSubstitueix);

	jsonFile.open("results.json");
	jsonFile << setw(4) << output << endl;
	jsonFile.close();

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Final del test sense errors" << endl;

	return 0;
}
