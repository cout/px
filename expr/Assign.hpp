#ifndef ASSIGN__HPP
#define ASSIGN__HPP

#include "Expression.hpp"

class Assign
  : public Expression
{
public:
  std::string slot;
  Ref<Expression> value;

  virtual std::string to_string() const { return slot + "=" + value->to_string(); }
  virtual Ref<Object> eval() { return Nil; }
};

#endif

