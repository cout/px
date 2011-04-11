#ifndef FLOAT__HPP
#define FLOAT__HPP

#include "Object.hpp"

class Float
  : public Object
{
public:
  Float(double d) : d(d) { }

  double d;
};

#endif

