#ifndef Token__hpp_
#define Token__hpp_

#include <string>

// TODO: use boost::any
struct Token {
  char const * ts;
  char const * te;
  int ival;
  double dval;
};

extern Token p_token;

#endif // Token__hpp_
