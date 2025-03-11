#pragma once
#include <iostream>
using namespace std;
class Complex
{
public:
	Complex() { m_real = 0; m_img = 0; }
	float getReal() { return m_real; }
	float getImg() { return m_img; }
	void setReal(int real) { m_real = real; }
	void setImg(int img) { m_img = img; }
	//Complex suma(const Complex &c) const;
	Complex operator+(const Complex &c) const;
	Complex operator-(const Complex &c) const;
	Complex operator*(const Complex &c) const;
private:
	float m_real, m_img;
};


istream& operator >> (istream& input, Complex& c);
ostream& operator<<(ostream& output, Complex& c);



