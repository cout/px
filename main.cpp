#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iostream>

#include <unistd.h>

#include "Token.hpp"
#include "scanner.hpp"

void *PParseAlloc(void *(*mallocProc)(size_t));
void PParseFree(void *p, void (*freeProc)(void*));
void PParse(void *yyp, int yymajor, Token yyminor);

typedef struct yy_buffer_state * YY_BUFFER_STATE;

namespace
{

void parse_file(void * parser, std::istream & in)
{
  PScanner scanner;
  // int yv = scanner.next_token();
  // PParse(parser, yv, scanner.token());
}

class ParserGuard
{
public:
  ParserGuard()
    : parser(PParseAlloc(std::malloc))
  {
  }

  ~ParserGuard()
  {
    PParseFree(parser, std::free);
  }

public:
  void * parser;
};

}

int main()
{
  ParserGuard pg;
  parse_file(pg.parser, std::cin);
}

