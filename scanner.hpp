#ifndef SCANNER__HPP
#define SCANNER__HPP

#include "Token.hpp"

#include <iosfwd>

class PScanner
{
public:
  PScanner();

  int p_scan(std::istream & in);

  Token const & token() { return token_; }

private:
  Token token_;
};

#endif
