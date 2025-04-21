#ifndef POSICIO_H
#define POSICIO_H


#include <iostream>
using namespace std;



class Posicio 
{

public:
    Posicio(const string& pos);
    

    bool operator==(const Posicio& pos) const;

    
private:
    
};

ostream& operator<<(ostream& out, const Posicio& pos);

#endif 