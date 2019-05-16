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

  if (s1 <= 0) {

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

NAN_METHOD(Line::intersects) {
  // Get the FunctionTemplate for the Line object
  v8::Local<v8::FunctionTemplate> tpl = Line::tpl().Get(info.GetIsolate());
  // Persist this template for later


  // Get the MaybeLocal<Object> version of the argument to run typechecking
  // against
  Nan::MaybeLocal<v8::Object> arg = Nan::To<v8::Object>(info[0]);

  if (arg.IsEmpty() || !tpl->HasInstance(info[0])) {
    Nan::ThrowTypeError(
        "Argument cannot be empty or not an instance of a wrapped Line Object");
    return;
  }
  // Unwrap "This" into the native object context
  Line *thiz = Nan::ObjectWrap::Unwrap<Line>(info.Holder());
  // Unwrap the argument into a native object context
  Line *other = Nan::ObjectWrap::Unwrap<Line>(arg.ToLocalChecked());
  // Set the return value directly to the result of the native function
  // invocation
  info.GetReturnValue().Set(thiz->intersects(other));
}

NAN_MODULE_INIT(Line::Init) {
  // Create the FunctionTemplate for New
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

  // Define our Object Properties
  tpl->SetClassName(Nan::New<v8::String>("Line").ToLocalChecked());
  // One Internal field count means we only have one wrapped object per
  // info.Holder context this might be variable for things like native array
  // implementations
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Hook our NAN_METHOD declarations
  Nan::SetPrototypeMethod(tpl, "intersects", intersects);

  // Set the static constructor reference
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Line::tpl().Reset(tpl);

  // Add the class to the native module exports
  Nan::Set(target, Nan::New<v8::String>("Line").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Line::New) {
  // Get the FunctionTemplate for the Point object
  v8::Local<v8::FunctionTemplate> tpl = Point::tpl().Get(info.GetIsolate());
  // If we're in a 'new Line()' context
  if (info.IsConstructCall()) {
    // Check to see if we're copying from two points or from 4 numbers
    if (info.Length() == 4) {
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

      // Take our current context and wrap the object in it
      thiz->Wrap(info.This());

      // Return the current context which contains the new native object
      // instance
      info.GetReturnValue().Set(info.This());
    } else {
      // assume we're using the Point init, throw otherwise
      // Even though we know the first one is a wrapped Point, we should check
      // both to prevent segfault/instance corruption
      if (!tpl->HasInstance(info[0]) || !tpl->HasInstance(info[1])) {
        Nan::ThrowTypeError(
            "Arguments are not native wrapped instances of Point object");
        return;
      }
      // Create v8 objects out of the argument values
      Nan::MaybeLocal<v8::Object> arg1 = Nan::To<v8::Object>(info[0]);
      Nan::MaybeLocal<v8::Object> arg2 = Nan::To<v8::Object>(info[1]);
      // Unwrap the objects into their native counterparts
      Point *a = Nan::ObjectWrap::Unwrap<Point>(arg1.ToLocalChecked());
      Point *b = Nan::ObjectWrap::Unwrap<Point>(arg2.ToLocalChecked());

      Line *thiz = new Line(a, b);
      // Wrap the current context around the new native object
      thiz->Wrap(info.This());

      // return the current context
      info.GetReturnValue().Set(info.This());
    }
  } else {
    if (info.Length() > 2) {
      const int argc = 4;
      v8::Local<v8::Value> argv[argc] = {info[0], info[1], info[2], info[3]};
      v8::Local<v8::Function> cons = Nan::New(Line::constructor());
      info.GetReturnValue().Set(
          Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    } else {
      const int argc = 2;
      v8::Local<v8::Value> argv[argc] = {info[0], info[1]};
      v8::Local<v8::Function> cons = Nan::New(Line::constructor());
      info.GetReturnValue().Set(
          Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }
}
