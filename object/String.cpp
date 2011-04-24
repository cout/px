#include "String.hpp"
#include "Nil.hpp"

#include "../context/Context.hpp"

#include <iostream>

class Local_Getter
  : public Object
{
public:
  virtual std::string to_string() const
  {
    return "Local_Getter";
  }

  virtual Ref<Object> receive(
    Ref<Object> recv,
    Ref<Expression> /* msg */,
    Ref<Context> context)
  {
    return context->getattr(recv);
  }
};

class Local_Setter
  : public Object
{
public:
  virtual std::string to_string() const
  {
    return "Local_Setter";
  }

  virtual Ref<Object> receive(
    Ref<Object> recv,
    Ref<Expression> msg,
    Ref<Context> context)
  {
    Ref<Object> value = msg->eval(context);
    context->setattr(recv, value);
    return value;
  }
};

class String_Prototype
  : public Object
{
public:
  typedef Object Super;

  virtual std::string to_string() const
  {
    return "String_Prototype";
  }

  String_Prototype()
    : Object(Object::make_prototype())
  {
  }

  class Bootstrapper
  {
  public:
    Bootstrapper(String_Prototype & p)
    {
      p.bootstrap();
    }
  };

  void bootstrap()
  {
    setattr("local_get", new Local_Getter);
    setattr("local_set", new Local_Setter);
  }

  virtual Ref<Object>
  getattr(
      Ref<Object> attr)
  {
    std::cout << "String prototype getattr " << attr->to_string();
    Bootstrapper bootstrapper(*this);
    return Super::getattr(attr);
  }
};

Ref<Object>
String::
make_prototype()
{
  static Ref<Object> prototype(new String_Prototype);
  return prototype;
}

