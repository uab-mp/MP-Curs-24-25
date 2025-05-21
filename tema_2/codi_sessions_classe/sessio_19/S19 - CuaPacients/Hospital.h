#pragma once
#include <queue>
#include <string>
using namespace std;

class Hospital
{
private:
	static const int N_CONSULTES = 3;
public:
	int registraPacient(const string &nom);
	string atendrePacient(int nConsulta);
};
