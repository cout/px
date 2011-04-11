#ifndef NIL__HPP
#define NIL__HPP

#include "Object.hpp"

class NilType
  : public Object
{
public:
  virtual std::string to_string() const { return "nil"; }
};

extern Ref<NilType> Nil;

#endif
