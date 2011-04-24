#ifndef STRING__HPP
#define STRING__HPP

#include "Object_T.hpp"

#include <string>

class String
  : public Object_T<std::string>
{
public:
  typedef Object_T<std::string> Super;

  static Ref<Object> make_prototype();

  String(std::string const & value)
    : Super(value, make_prototype())
  {
  }

  String(char const * p, char const * pe)
    : Super(std::string(p, pe), make_prototype())
  {
  }
};

#endif

