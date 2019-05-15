#include "Line.hpp"

Line::Line(Point a, Point b) {
    this->a = a;
    this->b = b;
}

Line::Line(double x1, double y1, double x2, double y2) {
    this->a = Point(x1, y1);
    this->b = Point(x2, y2);
}

int Line::intersects(Line* other) {
    return 0;
}