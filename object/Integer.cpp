#include "Integer.hpp"
#include "String.hpp"
#include "Nil.hpp"
#include "../function/Cxx_Member_Function.hpp"

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

