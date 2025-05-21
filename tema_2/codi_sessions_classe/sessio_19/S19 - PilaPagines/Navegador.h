#pragma once

#include <stack>
#include <string>
using namespace std;

class Navegador
{
private:
	string m_paginaActual;

public:
	Navegador() { m_paginaActual = "Pagina Inicial"; }
	void anarEnrere();
	void anarEndavant();
	void visitarNovaPagina(const string &url);
	const string& getPaginaActual() const { return m_paginaActual; }
};