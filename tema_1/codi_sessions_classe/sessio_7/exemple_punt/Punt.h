#ifndef PUNT_H
#define PUNT_H

#include <iostream>
using namespace std;

class Punt
{
    public:
        Punt() : m_x(0), m_y(0) { }
        Punt(float x, float y);
        ~Punt() {}
        float getX() const { return m_x; }
        void setX(const float x) { m_x = x; }
        float getY() const { return m_y; }
        void setY(const float y) { m_y = y; }
        void llegeix();
        void mostra();
        Punt suma(Punt& p);
    private:
        float m_x;
        float m_y;
};

#endif // PUNT_H
