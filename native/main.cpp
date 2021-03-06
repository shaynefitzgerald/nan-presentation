#include <nan.h>

#include "point/Point.hpp"
#include "line/Line.hpp"
#include "polygon/Polygon.hpp"

NAN_METHOD(SlickerAlgorithm) {
  if (!info[0]->IsArray()) {
    Nan::ThrowTypeError("Argument must be array");
    return;
  }

  v8::Local<v8::Array> points = v8::Local<v8::Array>::Cast(info[0]);

  if (points->Length() % 2 != 0) {
    Nan::ThrowRangeError("Argument length must be even");
  }

  Polygon poly(points->Length() / 2);

  for (unsigned int i = 0; i < points->Length() - 1; i += 2) {

    v8::Local<v8::Value> x = Nan::Get(points, i).ToLocalChecked();
    v8::Local<v8::Value> y = Nan::Get(points, i + 1).ToLocalChecked();

    Point *pt = new Point(x->NumberValue(Nan::GetCurrentContext()).ToChecked(),
                          y->NumberValue(Nan::GetCurrentContext()).ToChecked());
    poly.addPoint(pt);
  }

  double ret = poly.area();

  info.GetReturnValue().Set(ret);
}

NAN_MODULE_INIT(Init) {
  Point::Init(target);
  Line::Init(target);
  Nan::Set(target, Nan::New<v8::String>("computeSlickerArea").ToLocalChecked(),
           Nan::New<v8::FunctionTemplate>(SlickerAlgorithm)->GetFunction());
}

NODE_MODULE(addon, Init);
