#include "Line.hpp"

int Line::intersects(Line *other) {
  double x1, x2, y1, y2, p1, p2, q1, q2;

  x1 = this->a->x;
  x2 = this->b->x;
  y1 = this->a->y;
  y2 = this->b->y;

  p1 = other->a->x;
  p2 = other->b->x;
  q1 = other->a->y;
  q2 = other->b->y;

  int s1 = (y2 - y1) * p1 + (x1 - x2) * q1 + (x2 * y1 - x1 * y2);

  if (s1) {

    int s2 = (y2 - y1) * p2 + (x1 - x2) * q2 + (x2 * y1 - x1 * y2);

    if (s2 >= 0) {
      return 1;
    } else {
      return 0;
    }
  } else if (s1 > 0) {

    int s2 = (y2 - y1) * p2 + (x1 - x2) * q2 + (x2 * y1 - x1 * y2);

    if (s2 <= 0) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return -1;
  }
}
