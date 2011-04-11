#ifndef INTEGER__HPP
#define INTEGER__HPP

#include "Object.hpp"

class Integer
  : public Object
{
public:
  Integer(long i) : i(i) { }

  long i;
};

#endif
 
