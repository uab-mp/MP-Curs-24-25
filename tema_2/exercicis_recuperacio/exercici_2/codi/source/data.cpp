#include "data.h"

bool Data::dataValida() const
{
	bool correcte = false;
	if ((m_mes > 0) && (m_mes <= N_MESOS))
		if ((m_dia > 0) && (m_dia <= nDiesMes[m_mes-1]))
			correcte = true;
	return correcte;
}

Data Data::operator+(int nDies) const
{
	Data dataNova(*this);
	while (nDies > 0)
	{
		int diaAux = dataNova.m_dia + nDies;
		if (diaAux > nDiesMes[dataNova.m_mes-1])
		{
			nDies -= (nDiesMes[dataNova.m_mes-1] - dataNova.m_dia + 1);
			dataNova.m_dia = 1;
			dataNova.m_mes++;
			if (dataNova.m_mes > N_MESOS)
			{
				dataNova.m_any++;
				dataNova.m_mes = 1;
			}
		}
		else
		{
			dataNova.m_dia = diaAux;
			nDies = 0;
		}
	}
	return dataNova;
}


bool Data::operator==(const Data& data) const
{
	return ((m_dia == data.m_dia) && (m_mes == data.m_mes) && (m_any == data.m_any));
}

bool Data::operator<(const Data& data) const
{
	return ((m_any < data.m_any) || ((m_any == data.m_any) && (m_mes < data.m_mes)) ||
		((m_any == data.m_any) && (m_mes == data.m_mes) && (m_dia < data.m_dia)));
}

Data &Data::operator=(const Data& data)
{
	m_dia = data.m_dia;
	m_mes = data.m_mes;
	m_any = data.m_any;
	return *this;
}