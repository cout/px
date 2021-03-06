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
    return new Cxx_Member_Function<Object>(fun);
  }

  Object_Prototype()
    : Object(Ref<Object>(0))
  {
  }

  void bootstrap()
  {
    setattr("newline", memfun(&Object::newline));
    setattr("semicolon", memfun(&Object::semicolon));
    setattr("colon", memfun(&Object::colon));
    setattr("comma", memfun(&Object::comma));
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

  virtual std::string to_string() const {
    return "Object_Prototype";
  }
};

Ref<Object>
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
    Ref<Object> recv,
    Ref<Expression> msg,
    Ref<Context> context)
{
  std::stringstream strm;
  strm << "Object `" << this->to_string() << "'"
       << " cannot receive message `" << msg->to_string() << "'";

  if (recv.get() != this)
  {
    strm << " on behalf of " << recv->to_string();
  }

  throw std::runtime_error(strm.str());
}

std::ostream & operator<<(Object const & obj, std::ostream & strm)
{
  strm << obj.to_string();
  return strm;
}

std::ostream & operator<<(Ref<Object> const & obj, std::ostream & strm)
{
  // TODO: Could not get the following code to compile:
  //   strm << *obj;
  operator<<(*obj, strm);
  return strm;
}

Ref<Object>
Object::
newline(Ref<Object> msg)
{
  return msg;
}

Ref<Object>
Object::
semicolon(Ref<Object> msg)
{
  return msg;
}

Ref<Object>
Object::
comma(Ref<Object> msg)
{
  return msg;
}

Ref<Object>
Object::
colon(Ref<Object> msg)
{
  return msg;
}

