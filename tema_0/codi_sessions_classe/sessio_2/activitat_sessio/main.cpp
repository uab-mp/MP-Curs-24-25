#include <stdio.h>
#include <iostream>
#include "unio_vectors.h"

using namespace std;

template<typename T>
void mostraArray(T v[], int longitud)
{
	cout << "[";
	for (int i = 0; i < longitud - 1; i++)
		cout << v[i] << ", ";
	if (longitud > 0)
		cout << v[longitud - 1];
	cout << "]";
}

bool comparaVector(int v1[], int v2[], int longitud)
{
	bool iguals = true;
	int i = 0;
	while ((iguals) && (i < longitud))
	{
		if (v1[i] != v2[i])
			iguals = false;
		i++;
	}
	return iguals;
}


float testUnirNoOrdenats()
{
	float reduccio = 0.0;

	const int N_PROVES = 5;
	const int MAX_ELEMENTS = 10;

	int vector1[N_PROVES][MAX_ELEMENTS] = { { 1, 6, 5, 3, 9 },{ 5, 2, 1, 4, 3 },{ 6, 7, 8, 9, 10, 11 },{ 1, 3, 5, 9, 7, 10, 12 },{10,17,25,29,32} };
	int vector2[N_PROVES][MAX_ELEMENTS] = { { 4, 2, 8, 7, 6, 13 },{ 11, 10, 9, 8, 7, 6, 5 },{ 6, 5, 3, 4, 2, 1 },{ 2, 4, 6, 8, 10, 12 },{47,4,46,45,6,1} };
	int vectorUnio[MAX_ELEMENTS * 2];
	int vectorUnioEsperat[N_PROVES][MAX_ELEMENTS * 2] = {
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 13 },
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12 },
		{ 1, 4, 6,10,17,25,29,32,45, 46, 47 } };
	int midaVector1[N_PROVES] = { 5, 5, 6, 7, 5 };
	int midaVector2[N_PROVES] = { 6, 7, 6, 6, 6 };
	int midaVectorUnioEsperat[N_PROVES] = { 10, 11, 11, 11, 11 };
	int midaUnio = 0;
	

	cout << endl << endl;
	cout << "Comment :=>> Iniciant test Uneix Vectors No Ordenats" << endl;
	cout << "Comment :=>> =======================================" << endl;
	for (int i = 0; i < N_PROVES; i++)
	{
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Vector1: ";
		mostraArray(vector1[i], midaVector1[i]);
		cout << endl;
		cout << "Comment :=>> Vector2: ";
		mostraArray(vector2[i], midaVector2[i]);
		cout << endl;
		cout << "Comment :=>> ----------" << endl;
		cout << "Comment :=>> Resultat esperat:";
		mostraArray(vectorUnioEsperat[i], midaVectorUnioEsperat[i]);
		cout << endl;
		uneixVectors(vector1[i], midaVector1[i], vector2[i], midaVector2[i], vectorUnio, midaUnio);
		cout << "Comment :=>> ----------" << endl;
		cout << "Comment :=>> Resultat obtingut:";
		mostraArray(vectorUnio, midaUnio);
		cout << endl;
		if (comparaVector(vectorUnio, vectorUnioEsperat[i], midaVectorUnioEsperat[i]))
		{
			cout << "Comment :=>> CORRECTE" << endl;
		}
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2;
		}

		cout << "Comment :=>> -----------------------------------------------" << endl;
	}

	return reduccio;
}



int main()
{
	float grade = 0.0;

	cout << endl << endl;
	cout << "Comment :=>> INICIANT TEST" << endl;
	cout << "Comment :=>> =============" << endl;
	cout << "Comment :=>> " << endl;

	cout << "Grade :=>> " << grade << endl;
	float reduccio = testUnirNoOrdenats();
	if (reduccio > 10.0)
		reduccio = 10.0;
	grade = grade + (10 - reduccio);
	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}