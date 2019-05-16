#ifndef LINE_H
#define LINE_H

#include <nan.h>

#include "../point/Point.hpp"

class Line : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<v8::String>("Line").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(2);

    Nan::SetPrototypeMethod(tpl, "intersects", intersects);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(target, Nan::New<v8::String>("Line").ToLocalChecked(),
             Nan::GetFunction(tpl).ToLocalChecked());
  }

  static NAN_METHOD(New) {
    v8::Local<v8::FunctionTemplate> tpl =
        Nan::New<v8::FunctionTemplate>(Point::New);

    if (info.IsConstructCall()) {
      if (!tpl->HasInstance(info[0])) {
        // using the raw number initializer

        for (int i = 0; i < 4; i++) {
          if (info[i]->IsUndefined()) {
            Nan::ThrowTypeError("Arguments must not be undefined");
            return;
          }
        }

        double x1, y1, x2, y2;

        x1 = Nan::To<double>(info[0]).FromJust();
        y1 = Nan::To<double>(info[1]).FromJust();
        x2 = Nan::To<double>(info[2]).FromJust();
        y2 = Nan::To<double>(info[3]).FromJust();

        Line *thiz = new Line(x1, y1, x2, y2);

        thiz->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
      } else {
        // assume we're using the Point init, throw otherwise

        if (!tpl->HasInstance(info[1])) {
          Nan::ThrowTypeError(
              "Arguments are not native wrapped instances of Point object");
          return;
        }

        Nan::MaybeLocal<v8::Object> arg1 = Nan::To<v8::Object>(info[0]);
        Nan::MaybeLocal<v8::Object> arg2 = Nan::To<v8::Object>(info[1]);

        Point *a = Nan::ObjectWrap::Unwrap<Point>(arg1.ToLocalChecked());
        Point *b = Nan::ObjectWrap::Unwrap<Point>(arg2.ToLocalChecked());

        Line *thiz = new Line(a, b);

        thiz->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
      }
    } else {
      if (info.Length() > 2) {
        const int argc = 4;
        v8::Local<v8::Value> argv[argc] = {info[0], info[1], info[2], info[3]};
        v8::Local<v8::Function> cons = Nan::New(constructor());
        info.GetReturnValue().Set(
            Nan::NewInstance(cons, argc, argv).ToLocalChecked());
      } else {
        const int argc = 2;
        v8::Local<v8::Value> argv[argc] = {info[0], info[1]};
        v8::Local<v8::Function> cons = Nan::New(constructor());
        info.GetReturnValue().Set(
            Nan::NewInstance(cons, argc, argv).ToLocalChecked());
      }
    }
  }

  Point *a;
  Point *b;
  int intersects(Line *);

private:
  explicit Line(Point *a, Point *b) : a(a), b(b){};
  explicit Line(double x1, double y1, double x2, double y2)
      : a(new Point(x1, y1)), b(new Point(x2, y2)){};
  ~Line(){};

  static NAN_METHOD(intersects) {
    Nan::MaybeLocal<v8::Object> arg = Nan::To<v8::Object>(info[0]);

    if (arg.IsEmpty()) {
      return;
    }

    Line *thiz = Nan::ObjectWrap::Unwrap<Line>(info.Holder());

    Line *other = Nan::ObjectWrap::Unwrap<Line>(arg.ToLocalChecked());

    info.GetReturnValue().Set(thiz->intersects(other));
  }

  static inline Nan::Persistent<v8::Function> &constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
};

#endif // LINE_H