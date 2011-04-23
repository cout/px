#include "Undefined.hpp"
#include "String.hpp"

#include "../context/Context.hpp"
#include "../function/Cxx_Member_Function.hpp"

#include <iostream>

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
  }

  void bootstrap()
  {
    setattr("newline", memfun(&Object_Prototype::newline));
  }

  class Bootstrapper
  {
  public:
    Bootstrapper(Object_Prototype & p)
    {
      p.bootstrap();
    }
  };

  virtual Ref<Object>
  getattr(
      Ref<Object> attr)
  {
    // Special case (since the chain has to end *somewhere*
    std::cout << "Object prototype getattr " << attr->to_string() << std::endl;

    Bootstrapper bootstrapper(*this);

    Slots::iterator it(slots.find(attr));
    if (it == slots.end())
    {
      std::cout << "Not found!" << std::endl;
      return new Undefined(attr, this);
    }
    else
    {
      std::cout << "Found: " << it->second->to_string() << std::endl;
      return it->second;
    }
  }

  Ref<Object> newline(Ref<Object> msg) {
    return msg;
  }

  virtual std::string to_string() const {
    return "Object_Prototype";
  }
};

Ref<Object_Prototype>
Object::
make_prototype()
{
  static Ref<Object_Prototype> object_prototype;

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
  std::cout << "Object getattr " << attr->to_string() << std::endl;

  Slots::iterator it(slots.find(attr));
  if (it == slots.end())
  {
    Ref<Object> obj(prototype->getattr(attr));
    if (not obj->is_defined())
    {
      return new Undefined(attr, this);
    }
    else
    {
      return obj;
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

