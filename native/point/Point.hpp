#ifndef POINT_H
#define POINT_H

#include <nan.h>

class Point : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  explicit Point() : x(0), y(0){};
  explicit Point(Point *p) : x(p->x), y(p->y){};
  explicit Point(double x, double y) : x(x), y(y){};
  ~Point() {};
  double x, y;
  static inline Nan::Persistent<v8::FunctionTemplate> &tpl() {
    static Nan::Persistent<v8::FunctionTemplate> tpl;
    return tpl;
  }
private:
  static inline Nan::Persistent<v8::Function> &constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
};

#endif // POINT_H