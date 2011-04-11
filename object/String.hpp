#ifndef STRING__HPP
#define STRING__HPP

#include "Object.hpp"

#include <string>

class String
  : public Object
{
public:
  String(std::string const & str) : str(str) { }

  std::string str;
};

#endif

