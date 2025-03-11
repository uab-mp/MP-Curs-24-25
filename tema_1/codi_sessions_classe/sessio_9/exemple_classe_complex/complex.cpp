#include "complex.h"
#include <iostream>
using namespace std;

istream& operator>>(istream& input, Complex& c)
{
	float real, img;
	cout << "Part real: ";
	input >> real;
	cout << "Part imaginaria: ";
	input >> img;
	c.setReal(real);
	c.setImg(img);
	return input;
}

ostream& operator<<(ostream& output, Complex& c)
{
	output << c.getReal() << "+" << c.getImg() << "i";
	return output;
}

Complex Complex::operator+(const Complex &c) const
{
	Complex resultat;

	resultat.m_real = m_real + c.m_real;
	resultat.m_img = m_img + c.m_img;
	return resultat;
}

Complex Complex::operator-(const Complex &c) const
{
	Complex resultat;

	resultat.m_real = m_real - c.m_real;
	resultat.m_img = m_img - c.m_img;
	return resultat;
}

Complex Complex::operator*(const Complex &c) const
{
	Complex resultat;

	resultat.m_real = (m_real*c.m_real) - (m_img*c.m_img);
	resultat.m_img = (m_real*c.m_img) + (m_img*c.m_real);
	return resultat;
}