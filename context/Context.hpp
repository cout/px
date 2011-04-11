#ifndef CONTEXT__HPP
#define CONTEXT__HPP

#include "../object/Object.hpp"

class Context
  : public Object
{
  virtual std::string to_string() const { return "CONTEXT"; }
};

#endif
