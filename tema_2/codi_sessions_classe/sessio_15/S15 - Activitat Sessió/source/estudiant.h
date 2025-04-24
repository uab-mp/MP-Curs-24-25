#ifndef ESTUDIANT_H
#define ESTUDIANT_H
#include <string>
using namespace std;

class Estudiant
{
public:
	Estudiant();
    Estudiant(const string& niu, const string& nom, int nAssignatures);
	~Estudiant();

	Estudiant& operator=(const Estudiant& e);

	string getNiu() const { return m_NIU; }
	string getNom() const { return m_nom; }
	void setNiu(const string& niu) { m_NIU = niu; }
	void setNom(const string& nom) { m_nom = nom; }

	void afegeixAssignatura(const string& assignatura); 
	int getNAssignatures() const { return m_nAssignatures; }
	string getAssignatura(int posicio) const; 

	void allibera();
private:
	string m_nom;
	string m_NIU;
	string *m_assignatures;
	int m_maxAssignatures;
	int m_nAssignatures;
};

#endif