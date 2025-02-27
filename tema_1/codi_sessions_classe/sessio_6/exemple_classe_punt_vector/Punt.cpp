#pragma once
#include "Punt.h"
#include <cmath>
#include <iostream>
using namespace std;

void Punt::llegeix()
{
	cout << "Introdueix la dimensio del punt : ";
	cin >> m_nDimensio;
    cout << "Introdueix les " << m_nDimensio << " coordenades del punt : ";
    for (int i = 0; i < m_nDimensio; i++)
        cin >> m_coordenades[i];
}

void Punt::mostra()
{
    cout << "(";
    for (int i = 0; i < (m_nDimensio - 1); i++)
        cout << m_coordenades[i] << ", ";
    cout << m_coordenades[m_nDimensio - 1] << ")";
}

float Punt::distancia(Punt &p)
{
    float distancia = 0;
    for (int i = 0; i < m_nDimensio; i++)
    {
        float diferencia = p.m_coordenades[i] - m_coordenades[i];
        distancia += (diferencia * diferencia);
    }
    return sqrt(distancia);
}

Punt Punt::suma(Punt& p)
{
    Punt pSuma;
    pSuma.m_nDimensio = m_nDimensio;
    for (int i = 0; i < m_nDimensio; i++)
    {
        pSuma.m_coordenades[i] = m_coordenades[i] + p.m_coordenades[i];
    }
    return pSuma;
}
