#ifndef CXX_MEMBER_FUNCTION__HPP
#define CXX_MEMBER_FUNCTION__HPP

#include "Function.hpp"

#include <typeinfo>
#include <stdexcept>

template<typename T>
class Cxx_Member_Function
  : public Function
{
public:
  typedef Ref<Object> (T::*Func)(Ref<Object>);

  Func func;

  Cxx_Member_Function(Func func)
    : func(func)
  {
  }

  virtual Ref<Object> call(Ref<Object> recv, Ref<Object> msg, Ref<Context> context)
  {
    T * obj = dynamic_cast<T *>(recv.get());
    if (obj)
    {
      return ((*obj).*func)(msg);
    }
    else
    {
      throw std::runtime_error("Attempted to call function on wrong receiver type");
    }
  }

  virtual std::string to_string() const { return typeid(Func).name(); }
};

#endif
