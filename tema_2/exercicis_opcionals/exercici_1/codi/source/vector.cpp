#include"vector.h"

Vector::Vector()
{
	m_array = nullptr;
	m_nElements = 0;
	m_maxElements = 0;
}

Vector::Vector(const Vector& v)
{
	m_array = nullptr;
	m_maxElements = v.m_maxElements;
	m_nElements = v.m_nElements;
	if (v.m_array != nullptr)
	{
		m_array = new Punt[m_maxElements];
		for (int i = 0; i < v.m_nElements; i++)
		{
			m_array[i] = v.m_array[i];
		}
	}
}

Vector& Vector::operator=(const Vector& v)
{

}


Vector::~Vector()
{
	if (m_array != nullptr)
	{
		delete[] m_array;
		m_array = nullptr;
	}
	m_maxElements = 0;
	m_nElements = 0;
}



bool Vector::insereix(const Punt& pt, int posicio)
{

}

bool Vector::elimina(int posicio)
{

}


int Vector::getNElements()
{
	return m_nElements;
}

int Vector::getMaxElements()
{
	return m_maxElements;
}

Punt& Vector::operator[] (int nIndex)
{
	if (nIndex >= 0 && nIndex < m_nElements)
		return m_array[nIndex];
	else
	{
		cout << "Error d'acces a l'array" << endl;
		return m_valorDefecte;
	}
}




