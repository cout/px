#include "Integer.hpp"
#include "String.hpp"
#include "Nil.hpp"
#include "../function/Cxx_Member_Function.hpp"

Ref<Object>
Integer::
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
    if (name == Ref<String>(new String("plus")))
    {
      return new Cxx_Member_Function<Integer>(this, &Integer::plus);
    }
  }
}

Ref<Object>
Integer::
plus(
    Ref<Object> msg)
{
  Integer * i = dynamic_cast<Integer *>(msg.get());
  if (i)
  {
    return new Integer(this->value + i->value);
  }
}

