#ifndef CXX_MEMBER_FUNCTION__HPP
#define CXX_MEMBER_FUNCTION__HPP

#include "Function.hpp"

template<typename T>
class Cxx_Member_Function
  : public Function
{
public:
  typedef Ref<Object> (T::*Func)(Ref<Object>);

  Ref<T> instance;
  Func func;

  Cxx_Member_Function(Ref<T> instance, Func func)
    : instance(instance)
    , func(func)
  {
  }

  virtual Ref<Object> receive(Ref<Object> msg, Ref<Context> context)
  {
    return new String("RECEIVED");
  }

  virtual std::string to_string() const { return "FUNCTION"; }
};

#endif
