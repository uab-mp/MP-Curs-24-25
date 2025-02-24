#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

typedef struct {
	unsigned long dia;
	unsigned long mes;
	unsigned long any;
} Data;

// exercici 2
void llegeixDia(Data& diaCalendari);
bool esValida(Data& diaCalendari);
int comparaDates(Data& data1, Data& data2);
Data sumaDies(Data& diaOriginal, int nDies);
int restaDates(Data& data1, Data& data2);
bool terminiValid(Data& diaOriginal, int nDies, Data& dataActual);


#endif