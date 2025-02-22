#include <string>
using namespace std;

const int MAX_ASSIGNATURES = 10;
const int MAX_ESTUDIANTS = 100;



typedef struct 
{

} Assignacio; 

void inicialitza(Assignacio& dadesAssignacio, int nAssignatures, string nomAssignatures[MAX_ASSIGNATURES], int maxMatriculats[MAX_ASSIGNATURES]);
void afegeixPreferenciesEstudiant(Assignacio& dadesAssignacio, std::string nomEstudiant, int nCreditsSuperats, float notaMitjana, int nAssignaturesAMatricular, int nAssignaturesPreferides, string assignaturesPreferides[MAX_ASSIGNATURES]);
void fesAssignacio(Assignacio& dadesAssignacio);
void assignaturesEstudiant(Assignacio& dadesAssignacio, string nomEstudiant, int& nAssignatures, string assignaturesAssignades[MAX_ASSIGNATURES]);
void estudiantsAssignatura(Assignacio& dadesAssignacio, string nomAssignatura, int& nEstudiants, string estudiantsAssignats[MAX_ESTUDIANTS]);
