#ifndef ESTUDIANT_H
#define ESTUDIANT_H
#include <string>
#include <vector>
using namespace std;

class Estudiant
{
public:
	Estudiant(): m_NIU(""), m_nom("") {};
	Estudiant(const string& niu, const string& nom, int anyInici);
	~Estudiant();

	string getNiu() const { return m_NIU; }
	string getNom() const { return m_nom; }
	int getAnyInici() const { return m_anyInici; }
	void setNiu(const string& niu) { m_NIU = niu; }
	void setNom(const string& nom) { m_nom = nom; }
	void setAnyInici(int any) { m_anyInici = any; }

	void afegeixAssignatura(const string& assignatura); 
	void insereixAssignatura(const string& assignatura);
	void eliminaAssignatura(const string& assignatura);
	void mostraAssignatures();
	int getNAssignatures() const { return m_assignatures.size(); }
	string getAssignatura(int posicio) const; 

	void inicialitza(const string& niu, const string& nom);
	void allibera();
private:
	string m_nom;
	string m_NIU;
	int m_anyInici;
	vector<string> m_assignatures;
};
#endif