#ifndef INTEGER__HPP
#define INTEGER__HPP

#include "Object_T.hpp"

class Integer
  : public Object_T<long>
{
public:
  Integer(long value) : Object_T<long>(value) { }
};

#endif
 
