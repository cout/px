#ifndef BLOCK__HPP
#define BLOCK__HPP

#include "Expression.hpp"

class Block
  : public Expression
{
public:
  Block(Expression * next) : next(next) { }

  Ref<Expression> next;

  virtual std::string to_string() const { return std::string("{") + next->to_string() + "}"; }
  virtual Ref<Object> eval(Ref<Context> context) { return next->eval(context); }
};

#endif

