#include "Undefined.hpp"
#include "String.hpp"

#include "../context/Context.hpp"
#include "../function/Cxx_Member_Function.hpp"

class Object_Prototype
  : public Object
{
public:
  template<typename T>
  Ref<Function> memfun(T const & fun)
  {
    return new Cxx_Member_Function<Object_Prototype>(this, fun);
  }

  Object_Prototype()
    : Object(Ref<Object>(0))
  {
    setattr("newline", memfun(&Object_Prototype::newline));
  }

  Ref<Object> newline(Ref<Object> msg) {
    return msg;
  }

  virtual std::string to_string() const {
    return "Object_Prototype";
  }
};

Ref<Object>
Object::
make_prototype()
{
  static Ref<Object> object_prototype;

  if (not object_prototype.get())
  {
    object_prototype = new Object_Prototype;
  }

  return object_prototype;
}

Object::
Object()
  : prototype(make_prototype())
{
}

Object::
Object(Ref<Object> prototype)
  : prototype(prototype)
{
}

Ref<Object>
Object::
eval(
    Ref<Context> /* context */)
{
  return this;
}

Ref<Object>
Object::
getattr(
    Ref<Object> attr)
{
  Slots::iterator it(slots.find(attr));
  if (it == slots.end())
  {
    if (not prototype->getattr(attr)->is_defined())
    {
      return new Undefined(attr, this);
    }
  }
  else
  {
    return it->second;
  }
}

Ref<Object>
Object::
getattr(
    char const * s)
{
  return getattr(new String(s));
}


void
Object::
setattr(
    Ref<Object> name,
    Ref<Object> value)
{
  slots[name] = value;
}

void
Object::
setattr(
    char const * name,
    Ref<Object> value)
{
  return setattr(new String(name), value);
}

Ref<Object>
Object::
receive(
    Ref<Expression> msg,
    Ref<Context> context)
{
  std::stringstream strm;
  strm << "Object `" << this->to_string() << "'"
       << " cannot receive message `" << msg->to_string() << "'";
  throw std::runtime_error(strm.str());
}

