#include "Navegador.h"
#include <iostream>
using namespace std;

int main()
{
	Navegador n;

	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Visitar nova pagina: pagina_1" << endl;
	n.visitarNovaPagina("pagina_1");
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Visitar nova pagina: pagina_2" << endl;
	n.visitarNovaPagina("pagina_2");
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Visitar nova pagina: pagina_3" << endl;
	n.visitarNovaPagina("pagina_3");
	cout << "Pagina actual: " << n.getPaginaActual() << endl;

	cout << "Anar enrere" << endl;
	n.anarEnrere();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Anar enrere" << endl;
	n.anarEnrere();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Anar enrere" << endl;
	n.anarEnrere();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Anar enrere" << endl;
	n.anarEnrere();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;

	cout << "Anar endavant" << endl;
	n.anarEndavant();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Anar endavant" << endl;
	n.anarEndavant();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Anar endavant" << endl;
	n.anarEndavant();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Anar endavant" << endl;
	n.anarEndavant();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;
	cout << "Anar enrere" << endl;
	n.anarEnrere();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;

	cout << "Visitar nova pagina: pagina_4" << endl;
	n.visitarNovaPagina("pagina_4");
	cout << "Nova Pagina: " << n.getPaginaActual() << endl;
	cout << "Anar endavant" << endl;
	n.anarEndavant();
	cout << "Nova Pagina: " << n.getPaginaActual() << endl;
	cout << "Anar enrere" << endl;
	n.anarEnrere();
	cout << "Pagina actual: " << n.getPaginaActual() << endl;

	return 0;
}