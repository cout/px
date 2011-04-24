#include "Function.hpp"

#include "../object/Nil.hpp"

#include <iostream>

class Caller
  : public Object
{
public:
  virtual std::string to_string() const
  {
    return "Caller";
  }

  Ref<Object>
  receive(Ref<Object> recv, Ref<Object> msg, Ref<Context> context)
  {
    std::cout << recv->to_string() << std::endl;
    std::cout << msg->to_string() << std::endl;
    return Nil;
  }
};

class Function_Prototype
  : public Object
{
public:
  virtual std::string to_string() const
  {
    return "Function_Prototype";
  }

  Function_Prototype()
  {
    setattr("call", new Caller);
  }
};

Ref<Object>
Function::
make_prototype()
{
  Ref<Object> prototype(new Function_Prototype);
  return prototype;
}

Function::
Function()
  : Object(make_prototype())
{
}

Ref<Object>
Function::
receive(Ref<Object> recv, Ref<Object> msg, Ref<Context> context)
{
  return this->call(recv, msg->eval(context), context);
}

