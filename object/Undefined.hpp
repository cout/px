#ifndef UNDEFINED__HPP
#define UNDEFINED__HPP

#include "Object.hpp"

#include <sstream>

class Undefined
  : public Object
{
public:
  Undefined(Ref<Object> attr, Ref<Object> obj)
    : attr(attr)
    , obj(obj)
  {
  }

  virtual std::string to_string() const { return "undefined"; }

  virtual Ref<Object> eval(Ref<Context> /* context */)
  {
    std::stringstream strm;
    strm << "No such slot " << attr->to_string() << " in " << obj->to_string();
    throw std::runtime_error(strm.str());
  }

  Ref<Object> attr;
  Ref<Object> obj;
};

#endif
