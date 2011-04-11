#ifndef STRING__HPP
#define STRING__HPP

#include "Object_T.hpp"

#include <string>

class String
  : public Object_T<std::string>
{
public:
  String(std::string const & value) : Object_T<std::string>(value) { }

  String(char const * p, char const * pe) : Object_T<std::string>(std::string(p, pe)) { }
};

#endif

