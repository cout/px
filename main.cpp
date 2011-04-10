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

class Parser
  : public PScanner_Callback
{
public:
  Parser()
    : scanner_()
    , parser_(PParseAlloc(std::malloc))
  {
  }

  ~Parser()
  {
    PParseFree(parser_, std::free);
  }

  void parse_stream(std::istream & in)
  {
    scanner_.scan_stream(in, *this);
  }

protected:
  virtual void have_token(int id, Token const & token)
  {
    PParse(parser_, id, token);
  }

private:
  PScanner scanner_;
  void * parser_;
};

} // namespace

int main()
{
  try
  {
    Parser p;
    p.parse_stream(std::cin);
  }
  catch(std::exception const & ex)
  {
    std::cout << ex.what() << std::endl;
    return 1;
  }
  catch(...)
  {
    std::cout << "Unknown exception" << std::endl;
    return 1;
  }
}

