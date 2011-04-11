#ifndef NIL__HPP
#define NIL__HPP

#include "Object.hpp"

class NilType
  : public Object
{
};

extern Ref<NilType> Nil;

#endif
