#include "llista.h"

Llista::Llista(const Estudiant v[], int mida)
{
	if (mida <= MAX_ELEMENTS)
	{
		for (int i = 0; i < mida; i++)
		{
			m_elements[i] = v[i];
		}
		m_nElements = mida;
	}
}

bool Llista::pertany(const Estudiant& element) const
{
	bool trobat = false;
	int i = 0;
	while (!trobat && (i < m_nElements))
	{
		if (m_elements[i] == element)
			trobat = true;
		else
			i++;
	}
	return trobat;
}


int Llista::cerca(const string& niu) const
{
	bool trobat = false;
	int pos = -1;
	int i = 0;
	while (!trobat && (i < m_nElements))
	{
		if (m_elements[i].getNiu() == niu)
		{
			trobat = true;
			pos = i;
		}
		else
			i++;
	}
	return pos;
}


Estudiant Llista::getElement(int posicio) const
{
	if ((posicio >= 0) && (posicio < m_nElements))
		return m_elements[posicio];
	else
	{
		return Estudiant("","");
	}
}

void Llista::setElement(int posicio, const Estudiant& estudiant)
{
	if ((posicio >= 0) && (posicio < m_nElements))
		m_elements[posicio] = estudiant;
}

bool Llista::insereix(const Estudiant& element, int posicio)
{
	bool resultat = false;
	if ((m_nElements < MAX_ELEMENTS) && (posicio >= 0) && (posicio <= m_nElements))
	{
		resultat = true;
		for (int i = m_nElements; i > posicio; i--)
		{
			m_elements[i] = m_elements[i - 1];
		}		
		m_elements[posicio] = element;
		m_nElements++;
	}
	return resultat;
}

bool Llista::elimina(int posicio)
{
	bool resultat = false;
	if ((posicio >= 0) && (posicio < m_nElements))
	{
		resultat = true;
		for (int i = posicio; i < (m_nElements - 1); i++)
		{
			m_elements[i] = m_elements[i + 1];
		}
		m_nElements--;
	}
	return resultat;
}

bool Llista::operator+(const Estudiant& element)
{
	bool resultat = false;
	if (m_nElements < MAX_ELEMENTS)
	{
		resultat = true;
		m_elements[m_nElements] = element;
		m_nElements++;
	}
	return resultat;
}

bool Llista::operator-(const Estudiant& element)
{
	bool trobat = false;
	int posicio = 0;
	while (!trobat && (posicio < m_nElements))
	{
		if (m_elements[posicio] == element)
			trobat = true;
		else
			posicio++;
	}
	if (trobat)
	{
		for (int i = posicio; i < (m_nElements - 1); i++)
		{
			m_elements[i] = m_elements[i + 1];
		}
		m_nElements--;
	}
	return trobat;
}


ostream& operator<<(ostream& output, const Llista& llista)
{
	for (int i = 0; i < llista.getNumElements(); i++)
		output << llista.getElement(i) << endl;
	return output;
}

ofstream& operator<<(ofstream& output, const Llista& llista)
{
	for (int i = 0; i < llista.getNumElements(); i++)
		output << llista.getElement(i) << endl;
	return output;
}

ifstream& operator>>(ifstream& input, Llista& llista)
{
	Estudiant estudiant;
	input >> estudiant;
	while (!input.eof())
	{
		bool valid = llista + estudiant;
		input >> estudiant;
	}
	return input;
}
