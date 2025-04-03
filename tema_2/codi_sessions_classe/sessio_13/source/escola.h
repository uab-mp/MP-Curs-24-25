#ifndef ESCOLA_H
#define ESCOLA_H
#include "assignatura.h"
#include "professor.h"

const int MAX_ASSIGNATURES = 50;
const int MAX_PROFESSORS = 50;

class Escola
{
public:
    Escola() : m_nAssignatures(0), m_nProfessors(0) {}
    void inicialitzaAssignatures(const string& nomFitxer);
    void inicialitzaProfessors(const string& nomFitxer);
    bool afegeixProfessorAssignatura(const string& nomAssignatura, const string& nomProfessor);
    bool eliminaProfessorAssignatura(const string& nomAssignatura);
    void getAssignaturesProfessor(const string& nomProfessor, string assignatures[MAX_ASSIGNATURES], int& nAssignatures);
	string getProfessorAssignatura(const string& nomAssignatura);
private:
    Assignatura m_assignatures[MAX_ASSIGNATURES];
    int m_nAssignatures;
    Professor m_professors[MAX_PROFESSORS];
    int m_nProfessors;

    Assignatura* cercaAssignatura(const string& nomAssignatura);
    Professor* cercaProfessor(const string& nomProfessor);
};


#endif
