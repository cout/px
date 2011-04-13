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

