#ifndef FLOAT__HPP
#define FLOAT__HPP

#include "Object_T.hpp"

class Float
  : public Object_T<double>
{
public:
  Float(double value) : Object_T<double>(value) { }
};

#endif

