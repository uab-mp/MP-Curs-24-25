#ifndef PARAULOGIC_H
#define PARAULOGIC_H

const int MAX_PARAULA = 30;
const int N_LLETRES = 7;
const int N_PARAULES = 110000;

bool introdueixParaula(char paraula[MAX_PARAULA], char lletres[N_LLETRES],
	char diccionari[N_PARAULES][MAX_PARAULA], bool& tutti, int& puntuacio);

#endif

