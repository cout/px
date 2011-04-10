#ifndef SCANNER__HPP
#define SCANNER__HPP

#include "Token.hpp"

#include <iosfwd>

class PScanner
{
public:
  PScanner();

  int scan_stream(std::istream & in);

  Token const & token() { return token_; }

private:
  size_t buffer_space_remaining(size_t bufsize, size_t have);
  void check_for_error();
  void check_for_fragments(char const * p, char const * pe);

private:
  Token token_;

  static size_t const BUFSIZE = 1024;
  char inbuf_[BUFSIZE];
  size_t have_;

  int cs; // Ragel: current state
  int act; // Ragel: identity of last match
  char *ts; // Ragel: token start
  char *te; // Ragel: token end
};

#endif
