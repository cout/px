#include "Undefined.hpp"

#include "../context/Context.hpp"

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
    return new Undefined(attr, this);
  }
  else
  {
    return it->second;
  }
}

Ref<Object>
Object::
setattr(
    Ref<Object> attr,
    Ref<Object> value)
{
  slots[attr] = value;
}

Ref<Object>
Object::
receive(
    Ref<Expression> msg,
    Ref<Context> context)
{
  throw std::runtime_error("Object cannot receive messages");
}

