#include "Undefined.hpp"

inline
Ref<Object>
Object::
getattr(Ref<Object> attr) {
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

inline
Ref<Object>
Object::
receive(
    Ref<Object> name,
    Ref<Expression> msg,
    Ref<Context> context)
{
  Ref<Object> received_msg = msg->eval(context);
  Ref<Object> attr = getattr(name);
  // TODO: what now?
  return attr; // ???
}

