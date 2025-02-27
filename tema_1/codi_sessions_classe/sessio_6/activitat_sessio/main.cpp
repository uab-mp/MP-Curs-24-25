#include <iostream>
#include <math.h>
#include "array_estudiants.h"

using namespace std;


void mostraBool(bool resultat)
{
	if (resultat)
		cout << "CERT";
	else
		cout << "FALS";
}


float testAfegeixNota(Estudiant estudiants[], int& nEstudiants)
{
	float reduccio = 0.0;
	const int N_PROVES = 9;
	string niu[N_PROVES] = { "NIU_1", "NIU_2", "NIU_3", "NIU_5", "NIU_2", "NIU_2", "NIU_2", "NIU_2", "NIU_2" };
	float nota[N_PROVES] = { 5.0, 4.5, 6.5, 7.5, 5, 5.5, 7.0, 8.0, 6.0 };
	bool resultatEsperat[N_PROVES] = { true, true, true, false, true, true, true, true, false };

	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> -----------------------------------------------" << endl;
	cout << "Comment :=>> Test de la funcio afegeixNota " << endl;
	cout << "Comment :=>> -----------------------------------------------" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		bool resultat;

		cout << "Comment :=>>" << endl;
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> -----------------------------------------------" << endl;
		cout << "Comment :=>> Niu estudiant: " << niu[i] << endl;
		cout << "Comment :=>> Nota introduida: " << nota[i] << endl;
		cout << "Comment :=>> ----------" << endl;

		resultat = afegeixNota(estudiants, nEstudiants, niu[i], nota[i]);
		cout << "Comment :=>> Resultat esperat: ";
		mostraBool(resultatEsperat[i]);
		cout << endl;
		cout << "Comment :=>> ----------" << endl;
		cout << "Comment :=>> Resultat obtingut: ";
		mostraBool(resultat);
		cout << endl;
		cout << "Comment :=>> ----------" << endl;
		if (resultatEsperat[i] == resultat)
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2;
		}
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	return reduccio;
}


float testCalculaNotaMitjana(Estudiant estudiants[], int& nEstudiants)
{
	float reduccio = 0.0;
	const int N_PROVES = 4;
	string niu[N_PROVES] = { "NIU_1", "NIU_2", "NIU_4", "NIU_5"};
	float mitjanaEsperada[N_PROVES] = { 5.0, 6.0, -1.0, -1.0 };

	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> -----------------------------------------------" << endl;
	cout << "Comment :=>> Test de la funcio calculaNotaMitjana " << endl;
	cout << "Comment :=>> -----------------------------------------------" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		float resultat;

		cout << "Comment :=>>" << endl;
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> -----------------------------------------------" << endl;
		cout << "Comment :=>> Niu estudiant: " << niu[i] << endl;
		cout << "Comment :=>> ----------" << endl;

		resultat = calculaNotaMitjana(estudiants, nEstudiants, niu[i]);
		cout << "Comment :=>> Resultat esperat: " << mitjanaEsperada[i] << endl;
		cout << "Comment :=>> ----------" << endl;
		cout << "Comment :=>> Resultat obtingut: " << resultat << endl;
		cout << "Comment :=>> ----------" << endl;
		if (fabs(mitjanaEsperada[i] - resultat) < 0.001)
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2;
		}
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	return reduccio;
}


void inicialitzaTest(Estudiant estudiants[], int& nEstudiants)
{
	cout << "Comment :=>> Inicialitzem l'array d'estudiants...." << endl;
	cout << "Comment :=>> Afegim estudiant amb nom i niu: " << "NOM_1, NIU_1" << endl;
	afegeixEstudiant(estudiants, nEstudiants, "NOM_1", "NIU_1");
	nEstudiants++;
	cout << "Comment :=>> Afegim estudiant amb nom i niu: " << "NOM_2, NIU_2" << endl;
	afegeixEstudiant(estudiants, nEstudiants, "NOM_2", "NIU_2");
	nEstudiants++;
	cout << "Comment :=>> Afegim estudiant amb nom i niu: " << "NOM_3, NIU_3" << endl;
	afegeixEstudiant(estudiants, nEstudiants, "NOM_3", "NIU_3");
	nEstudiants++;
	cout << "Comment :=>> Afegim estudiant amb nom i niu: " << "NOM_4, NIU_4" << endl;
	afegeixEstudiant(estudiants, nEstudiants, "NOM_4", "NIU_4");
	nEstudiants++;
	cout << "Comment :=>> ----------------------------------" << endl;
}

int main()
{
	float grade = 0.0;

	cout << endl << endl;
	cout << "Comment :=>> INICIANT TEST" << endl;
	cout << "Comment :=>> =============" << endl;
	cout << "Comment :=>> " << endl;

	cout << "Grade :=>> " << grade << endl;

	Estudiant estudiants[MAX_ESTUDIANTS];
	int nEstudiants = 0;

	inicialitzaTest(estudiants, nEstudiants);

	float reduccio = testAfegeixNota(estudiants, nEstudiants);
	grade = grade + (5 - reduccio);
	if (grade < 0)
		grade = 0.0;
	reduccio = testCalculaNotaMitjana(estudiants, nEstudiants);
	grade = grade + (5 - reduccio);
	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}
