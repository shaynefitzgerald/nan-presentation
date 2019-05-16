
#include "Point.hpp"

NAN_METHOD(Point::New) {
  if (info.IsConstructCall()) {
    double x = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    double y = info[1]->IsUndefined() ? 0 : Nan::To<double>(info[1]).FromJust();

    Point *thiz = new Point(x, y);

    thiz->Wrap(info.This());

    info.GetReturnValue().Set(info.This());
  } else {
    if (info[0]->IsUndefined()) {
      // Since we know our constructor has a no argument constructor, we can
      // simply invoke that
      v8::Local<v8::Function> cons = Nan::New(constructor());

      // Note no argc/argv needed here
      info.GetReturnValue().Set(Nan::NewInstance(cons).ToLocalChecked());
      return;
    } else {

      // We make the assumption here that there are 2 args (really we only care
      // about 2 args)
      const int argc = 2;
      v8::Local<v8::Value> argv[argc] = {info[0], info[1]};

      v8::Local<v8::Function> cons = Nan::New(constructor());

      info.GetReturnValue().Set(
          Nan::NewInstance(cons, argc, argv).ToLocalChecked());
      return;
    }
  }
}

NAN_MODULE_INIT(Point::Init) {
  v8::Local<v8::FunctionTemplate> tpl =
      Nan::New<v8::FunctionTemplate>(Point::New);

  tpl->SetClassName(Nan::New("Point").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());

  Point::tpl().Reset(tpl);
  Nan::Set(target, Nan::New<v8::String>("Point").ToLocalChecked(),
            Nan::GetFunction(tpl).ToLocalChecked());
}