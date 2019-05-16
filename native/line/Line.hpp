#ifndef LINE_H
#define LINE_H

#include <nan.h>

#include "../point/Point.hpp"

class Line : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(New);

  Point *a;
  Point *b;
  static NAN_METHOD(intersects);
    static inline Nan::Persistent<v8::FunctionTemplate> &tpl() {
    static Nan::Persistent<v8::FunctionTemplate> tpl;
    return tpl;
  }
private:
  explicit Line(Point *a, Point *b) : a(a), b(b){};
  explicit Line(double x1, double y1, double x2, double y2)
      : a(new Point(x1, y1)), b(new Point(x2, y2)){};
  ~Line(){};
  int intersects(Line *);
  static inline Nan::Persistent<v8::Function> &constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
};

#endif // LINE_H