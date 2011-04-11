#ifndef EXPRESSION__HPP
#define EXPRESSION__HPP

#include "../object/Object.hpp"
#include "../object/Nil.hpp"

#include <string>

class Expression
  : public Object
{
public:
  virtual ~Expression() { }

  virtual std::string to_string() const = 0;
  virtual Ref<Object> eval() = 0;
};

#endif

