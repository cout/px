#ifndef SCANNER__HPP
#define SCANNER__HPP

#include "Token.hpp"

#include <iosfwd>

class PScanner_Callback
{
public:
  virtual ~PScanner_Callback() { }

  virtual void have_token(int id, Token const & token) = 0;
};

class PScanner
{
public:
  PScanner();

  int scan_stream(
      std::istream & in,
      PScanner_Callback & cb);

private:
  size_t buffer_space_remaining(size_t bufsize, size_t have);
  void check_for_error();
  void check_for_fragments(char const * p, char const * pe);

private:
  static size_t const BUFSIZE = 1024;
  char inbuf_[BUFSIZE];
  size_t have_;

  int cs; // Ragel: current state
  int act; // Ragel: identity of last match
  char *ts; // Ragel: token start
  char *te; // Ragel: token end
};

#endif
