#include <iostream>
using namespace std;

int main()
{
    int x, y;
    int *ptrX, *ptrY;

    x = 5;
    y = 0;

    ptrX = &x;
    y = *ptrX;
    *ptrX = 10;
    ptrY = &y;
    *ptrX = *ptrY + 2;
//	ptrY = nullptr;

    cout << "x: " << x << ", &x: " << &x << endl;
    cout <<	"y: " << y << ", &y: " << &y << endl; 
    cout << "*ptrX: " << *ptrX << ", ptrX: " << ptrX << endl;
    cout << "*ptrY: " << *ptrY << ", ptrY: " << ptrY << endl;
    return 0;

}