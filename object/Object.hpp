#ifndef OBJECT__HPP
#define OBJECT__HPP

#include "Ref.hpp"

#include <map>

class String;

class Object
{
public:
  std::map<Ref<Object>, Ref<Object> > slots;
};

#endif

