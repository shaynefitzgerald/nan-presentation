#ifndef POINT_H
#define POINT_H

#include <nan.h>

class Point : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Point").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(2);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  }
  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
        double x = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
        double y = info[1]->IsUndefined() ? 0 : Nan::To<double>(info[1]).FromJust();

        Point* thiz = new Point(x, y);
        
        thiz->Wrap(info.This());
        
        info.GetReturnValue().Set(info.This());
    } else {
        if(info[0]->IsUndefined()) {
            v8::Local<v8::Function> cons = Nan::New(constructor());           
            info.GetReturnValue().Set(Nan::NewInstance(cons).ToLocalChecked());
            return;
        } else {
            const int argc = 2;
            v8::Local<v8::Value> argv[argc] = {info[0], info[1]};
           
            v8::Local<v8::Function> cons = Nan::New(constructor());
           
            info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
            return;
        }
    }
  }
  explicit Point() : x(0), y(0) {};
  explicit Point(Point* p): x(p->x), y(p->y) {};
  explicit Point(double x, double y) : x(x), y(y) {};
  double x, y;

private:
  static inline Nan::Persistent<v8::Function> &constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
};

#endif // POINT_H