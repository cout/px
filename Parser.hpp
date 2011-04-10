#ifndef PARSER__HPP
#define PARSER__HPP

#include "Token.hpp"
#include "scanner.hpp"
#include "ast.hpp"

#include <cstdlib>

void *PParseAlloc(void *(*mallocProc)(size_t));
void PParseFree(void *p, void (*freeProc)(void*));
void PParse(void *yyp, int yymajor, Token yyminor, Expression * * root);
void PParseTrace(FILE * stream, char * zPrefix);

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

  void trace(std::ostream & out)
  {
    // TODO
  }

protected:
  virtual void have_token(int id, Token const & token)
  {
    Expression * root;
    PParse(parser_, id, token, &root);
  }

private:
  PScanner scanner_;
  void * parser_;
};

#endif // PARSER__HPP

