#ifndef OBJECT_T__HPP
#define OBJECT_T__HPP

#include "Object.hpp"

#include <boost/lexical_cast.hpp>

template<typename T>
class Object_T
  : public Object
{
public:
  Object_T(T value) : value(value) { }

  T value;

  virtual std::string to_string() const { return boost::lexical_cast<std::string>(value); }

  virtual bool operator<(Object const & rhs) const
  {
    Object_T<T> const * p_rhs = dynamic_cast<Object_T<T> const *>(&rhs);
    if (p_rhs)
    {
      return value < p_rhs->value;
    }
    else
    {
      throw std::runtime_error("Cannot compare different types");
    }
  }

  virtual bool operator==(Object const & rhs) const
  {
    Object_T<T> const * p_rhs = dynamic_cast<Object_T<T> const *>(&rhs);
    if (p_rhs)
    {
      return value == p_rhs->value;
    }
    else
    {
      throw std::runtime_error("Cannot compare different types");
    }
  }
};

#endif

