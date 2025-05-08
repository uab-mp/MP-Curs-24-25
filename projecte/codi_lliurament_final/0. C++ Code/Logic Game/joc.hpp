#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"

using namespace std;


class Joc 
{

public:
    Joc():m_fila(0), m_columna(0) {};
    
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    
    
private:

};

#endif 
