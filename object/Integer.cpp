#include "Integer.hpp"
#include "String.hpp"

Ref<Object>
Integer::
getattr(
    Ref<Object> name)
{
  Ref<Object> attr(Object::getattr(name));
  std::cout << "HERE" << std::endl;
  std::cout << attr.get() << std::endl;
  if (attr->is_defined())
  {
    return attr;
  }
  else
  {
    if (name == Ref<String>(new String("plus")))
    {
      std::cout << "PLUS!" << std::endl;
      return attr; // TODO
    }
  }
}

