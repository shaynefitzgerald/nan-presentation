
#ifndef LINE_H
#define LINE_H
#include "../point/Point.hpp"

class Line {
    Point a;
    Point b;
    Line(Point, Point);
    Line(double, double, double, double);
    int intersects(Line*);
};

#endif //LINE_H