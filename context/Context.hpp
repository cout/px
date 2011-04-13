#ifndef CONTEXT__HPP
#define CONTEXT__HPP

#include "../object/Object.hpp"
#include "../object/String.hpp"

class Context
  : public Object
{
public:
  Context() { }

  explicit Context(Ref<Context> parent)
  {
    setattr(new String("parent"), parent);
  }

  virtual std::string to_string() const { return "CONTEXT"; }
};

#endif
