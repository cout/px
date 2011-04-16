#ifndef INTEGER__HPP
#define INTEGER__HPP

#include "Object_T.hpp"

#include <iostream>

class Integer
  : public Object_T<long>
{
public:
  Integer(long value) : Object_T<long>(value) { }

  virtual Ref<Object> getattr(
      Ref<Object> name);

  virtual Ref<Object> plus(
      Ref<Object> msg);
};

#endif
 
