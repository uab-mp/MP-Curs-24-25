#ifndef ARRAY_ESTUDIANTS_H
#define ARRAY_ESTUDIANTS_H
#include "estudiant.h"

const int MAX_ESTUDIANTS = 10;

void afegeixEstudiant(Estudiant estudiants[], int nEstudiants, string nom, string niu);
bool afegeixNota(Estudiant estudiants[], int nEstudiants, string niu, float nota);
float calculaNotaMitjana(Estudiant estudiants[], int nEstudiants, string niu);

#endif