#include <iostream>
using namespace std;

class Complex
{
public:
	void setReal(float real) { m_real = real; }
	void setImg(float img) { m_img = img; }
	float getReal() const { return m_real; }
	float getImg() const { return m_img; }
private:
	float m_real;
	float m_img;
};

ostream& operator<<(ostream& out, const Complex& c)
{
	out << c.getReal() << " + " << c.getImg() << "i";
	return out;
}


int main()
{
    Complex numero1, numero2;
    Complex *ptrNumero1, *ptrNumero2;

    ptrNumero1 = &numero1;
    (*ptrNumero1).setReal(1.0);
    ptrNumero1->setImg(1.0);
    ptrNumero2 = &numero2;
    numero2.setReal(2.0);
    numero2.setImg(2.0);
    ptrNumero1->setReal(ptrNumero1->getReal() + ptrNumero2->getReal());
    ptrNumero1->setImg(numero1.getImg() * numero2.getImg());

    cout << "numero1: " << numero1 << endl;
    cout << "ptrNumero1: " << ptrNumero1 << endl;
    cout << "&numero1: " << &numero1 << endl;
    cout << "*ptrNumero1 " << *ptrNumero1 << endl;
    cout << "numero2: " << numero2 << endl;
    cout << "ptrNumero2: " << ptrNumero2 << endl;
    cout << "&numero2: " << &numero2 << endl;
    cout << "*ptrNumero2 " << *ptrNumero2 << endl;
    return 0;
}