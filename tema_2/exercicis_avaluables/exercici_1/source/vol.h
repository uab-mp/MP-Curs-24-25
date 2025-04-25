#ifndef VOL_H
#define VOL_H

#include "seient.h"
#include <string>
using namespace std;

class Vol
{
public:
	Vol();
	Vol(const string& codi, const string& origen, const string& desti,
		const string& data, const string& hora, int maxSeients);
	Vol(const Vol& v);
	Vol& operator=(const Vol& v);
	~Vol();

	void afegeixSeients(string* codiSeients, int nSeients);

	bool afegeixPassatger(const string& codiSeient, const string& dni, const string& nom);
	Passatger* recuperaPassatger(const string& codiSeient);
	bool cancelaReserva(const string& codiSeient);
	bool modificaReserva(const string& codiSeientOriginal, const string& codiSeientNou);
private:
	string m_codi;
	string m_origen;
	string m_desti;
	string m_data;
	string m_hora;
	Seient* m_seients;
	int m_maxSeients;
	int m_nSeients;
};

#endif
