#include "Function.hpp"
#include "String.hpp"

Ref<Object>
Function::
getattr(
    Ref<Object> name)
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
      return attr; // TODO
    }
  }
}

