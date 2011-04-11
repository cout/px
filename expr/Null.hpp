#ifndef NULL__HPP
#define NULL__HPP

#include "Expression.hpp"

class Null
  : public Expression
{
  virtual std::string to_string() const { return "()"; }
  virtual Ref<Object> eval() { return Nil; }
};

#endif

