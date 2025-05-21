#include "Hospital.h"
#include <iostream>
using namespace std;

int  main()
{
	Hospital h;
	int nConsulta;
	string nom;

	nom = "pacient_1";
	nConsulta = h.registraPacient(nom);
	cout << "Registre pacient " << nom << " a consulta " << nConsulta << endl;
	
	nom = "pacient_2";
	nConsulta = h.registraPacient(nom);
	cout << "Registre pacient " << nom << " a consulta " << nConsulta << endl;

	nom = "pacient_3";
	nConsulta = h.registraPacient(nom);
	cout << "Registre pacient " << nom << " a consulta " << nConsulta << endl;

	nom = "pacient_4";
	nConsulta = h.registraPacient(nom);
	cout << "Registre pacient " << nom << " a consulta " << nConsulta << endl;

	nConsulta = 2;
	nom = h.atendrePacient(nConsulta);
	cout << "Atencio pacient " << nom << " a consulta " << nConsulta << endl;

	nConsulta = 0;
	nom = h.atendrePacient(nConsulta);
	cout << "Atencio pacient " << nom << " a consulta " << nConsulta << endl;

	nom = "pacient_5";
	nConsulta = h.registraPacient(nom);
	cout << "Registre pacient " << nom << " a consulta " << nConsulta << endl;

	nConsulta = 0;
	nom = h.atendrePacient(nConsulta);
	cout << "Atencio pacient " << nom << " a consulta " << nConsulta << endl;

	nConsulta = 1;
	nom = h.atendrePacient(nConsulta);
	cout << "Atencio pacient " << nom << " a consulta " << nConsulta << endl;

	nConsulta = 2;
	nom = h.atendrePacient(nConsulta);
	cout << "Atencio pacient " << nom << " a consulta " << nConsulta << endl;

	nConsulta = 2;
	nom = h.atendrePacient(nConsulta);
	cout << "Atencio pacient " << nom << " a consulta " << nConsulta << endl;

	return 0;
}