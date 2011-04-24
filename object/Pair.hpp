#ifndef PAIR__HPP
#define PAIR__HPP

#include "Object_T.hpp"

#include <utility>

class Pair
  : public Object_T<std::pair<Object, Object> >
{
};

#endif
