#include <iostream>

using namespace std;

#include "polygon.hpp"

Polygon::Polygon(unsigned int sz) {
    this->sz = sz;
    this->p = new Point[sz];
    this->n = 0;
}

void Polygon::addPoint(Point pt) {
    this->p[this->n] = pt;
    this->n++;
}

double Polygon::area()
{
    double total = 0;
    for (int i = 0; i < this->n; i++)
    {
        int j = (i + 1) % this->n;
        total += (this->p[i].x * this->p[j].y) - (this->p[j].x * this->p[i].y);
    }
    return total / 2;
}
