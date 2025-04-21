#include "seient.h"
#include <iostream>
using namespace std;

void mostraBool(bool logic)
{
	if (logic)
		cout << "TRUE";
	else
		cout << "FALSE";
}

void mostraPassatger(Passatger* p)
{
	if (p == nullptr)
		cout << "nullptr";
	else
		if (p->getDni() == "")
			cout << "nullptr";
		else
			cout << p->getDni() << ", " << p->getNom();
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

float testSeient()
{
	float reduccio = 0.0;

	cout << "Comment :=>>" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> Iniciant test de la classe Seient" << endl;
	cout << "Comment :=>> =================================" << endl;
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

	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> Inicialitzant un seient amb codi 1A" << endl;
	Seient s("1A");

	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Valor esperat del passatger despres d'inicialitzar: ";
	mostraPassatger(nullptr);
	cout << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Valor obtingut del passatger despres d'inicialitzar: ";
	Passatger* p = s.getPassatger();
	mostraPassatger(p);
	cout << endl; 
	if (!igualsPassatgers(p, nullptr))
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 1.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;


	for (int i = 0; i < N_PROVES; i++)
	{
		bool resultat;
		Passatger* p;
		cout << "Comment :=>> ------------------------------------------" << endl;
		cout << "Comment :=>> TEST " << i + 1 << endl;
		if (operacio[i] == 'A')
		{
			cout << "Comment :=>> Afegint passatger al seient..." << endl;
			cout << "Comment :=>> Dades del passatger: "; mostraPassatger(&dadesPassatger[i]); cout << endl;
			cout << "Comment :=>> ---" << endl;
			cout << "Comment :=>> Valor retorn esperat: "; mostraBool(resultatEsperat[i]); cout << endl;
			cout << "Comment :=>> Passatger esperat: "; mostraPassatger(&valorEsperat[i]); cout << endl;
			cout << "Comment :=>> ---" << endl;
			resultat = s.assignaPassatger(dadesPassatger[i].getDni(), dadesPassatger[i].getNom());
			p = s.getPassatger();
			cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(resultat); cout << endl;
			cout << "Comment :=>> Passatger obtingut: "; mostraPassatger(p); cout << endl;
		}
		else
		{
			cout << "Comment :=>> Eliminant el passatger del seient..." << endl;
			cout << "Comment :=>> ---" << endl;
			cout << "Comment :=>> Valor retorn esperat: "; mostraBool(resultatEsperat[i]); cout << endl;
			cout << "Comment :=>> Passatger esperat: "; mostraPassatger(&valorEsperat[i]); cout << endl;
			cout << "Comment :=>> ---" << endl;
			resultat = s.eliminaPassatger();
			p = s.getPassatger();
			cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(resultat); cout << endl;
			cout << "Comment :=>> Passatger obtingut: "; mostraPassatger(p); cout << endl;
		}

		if ((resultat == resultatEsperat[i]) && igualsPassatgers(p, &valorEsperat[i]))
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
	}
	if (reduccio > 2.0)
		reduccio = 2.0;
	return reduccio;
}





int main()
{
	float grade = 0.0;
	float reduccio;

	cout << endl << endl;
	cout << "Comment :=>> INICIANT TEST" << endl;
	cout << "Comment :=>> =============" << endl;
	cout << "Comment :=>> " << endl;

	cout << "Grade :=>> " << grade << endl;
	reduccio = testSeient();
	grade = grade + (10 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << "Grade :=>> " << grade << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	return 0;
}