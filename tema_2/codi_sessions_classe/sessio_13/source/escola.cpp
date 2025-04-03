#include "escola.h"
#include <fstream>
using namespace std;

void Escola::inicialitzaProfessors(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        string nom, mail, despatx;
        while (!fitxer.eof())
        {
            fitxer >> nom >> mail >> despatx;
            m_professors[m_nProfessors++] = Professor(nom, mail, despatx);
        }
        fitxer.close();
    }
}

void Escola::inicialitzaAssignatures(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        string nomAssignatura;
        int nEstudiants;
        while (!fitxer.eof())
        {
            fitxer >> nomAssignatura >> nEstudiants;
            m_assignatures[m_nAssignatures] = Assignatura(nomAssignatura);
            for (int i = 0; i < nEstudiants; i++)
            {
                string nom, niu;
                fitxer >> nom >> niu;
                m_assignatures[m_nAssignatures].afegeixEstudiant(nom, niu);
            }
            m_nAssignatures++;
        }
        fitxer.close();
    }
}

