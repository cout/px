#ifndef Token__hpp_
#define Token__hpp_

struct Token {
  char const * sval;
  int ival;
  double dval;
};

extern Token p_token;

#endif // Token__hpp_
