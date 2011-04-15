#include "Function.hpp"
#include "../object/String.hpp"

#include <iostream>

Ref<Object>
Function::
receive(
    Ref<Object> name,
    Ref<Expression> msg,
    Ref<Context> context)
{
  Ref<Object> attr(Object::getattr(name));
  if (attr->is_defined())
  {
    return attr;
  }
  else
  {
    if (name == Ref<String>(new String("call")))
    {
      std::cout << "CALL!" << std::endl;
      return call(msg->eval(context));
    }
  }
}

