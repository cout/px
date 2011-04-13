#ifndef FUNCTION__HPP
#define FUNCTION__HPP

#include "Object.hpp"

#include <iostream>

class Function
  : public Object
{
public:
  Function() { }

  virtual Ref<Object> getattr(
      Ref<Object> name);
};

#endif
 
