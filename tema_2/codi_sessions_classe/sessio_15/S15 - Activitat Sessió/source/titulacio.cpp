#include "titulacio.h"



void Titulacio::afegeixEstudiant(const string& niu, const string& nom)
{

}

bool Titulacio::eliminaEstudiant(const string& niu)
{

}

bool Titulacio::consultaEstudiant(const string& niu, Estudiant& e)
{
	bool trobat = false;
	int i = 0;
	while ((i < m_nEstudiants) && !trobat)
	{
		if (niu == m_estudiants[i].getNiu())
			trobat = true;
		else
		{
			i++;
		}
	}
	if (trobat)
	  e = m_estudiants[i];
	return trobat;
}
