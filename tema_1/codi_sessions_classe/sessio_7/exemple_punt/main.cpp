#include "Punt.h"
#include <iostream>
using namespace std;

int main()
{
    Punt pt1(0, 0);
    
    for (int i = 0; i < 10; i++)
    {
        cout << "Iteracio del bucle " << i << endl;
        Punt pt2, pt3(-1, -1);
        pt2.llegeix();
        pt3 = pt1.suma(pt2);
        pt3.mostra();
        cout << "Final iteracio " << endl;
    }

    return 0;
}

/*int main()
{
    Punt pt1(0, 0);
    Punt llistaPunts[10];

    for (int i = 0; i < 10; i++)
    {
        cout << "Iteracio del bucle " << i << endl;
        Punt pt3(-1, -1);
        llistaPunts[i].llegeix();
        pt3 = pt1.suma(llistaPunts[i]);
        pt3.mostra();
        cout << "Final iteracio " << endl;
    }

    return 0;
}*/