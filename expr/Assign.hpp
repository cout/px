#ifndef ASSIGN__HPP
#define ASSIGN__HPP

#include "Expression.hpp"

#include "../object/Nil.hpp"
#include "../context/Context.hpp"

class Assign
  : public Expression
{
public:
  Ref<Object> slot;
  Ref<Expression> value;

  virtual std::string to_string() const { return slot->to_string() + "=" + value->to_string(); }
  virtual Ref<Object> eval(Ref<Context> context) {
    Ref<Expression> result = value->eval(context);
    context->slots[slot] = result;
    return result;
  }
};

#endif

