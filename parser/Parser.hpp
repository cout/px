#ifndef PARSER__HPP
#define PARSER__HPP

#include "Token.hpp"
#include "scanner.hpp"

#include "../object/Object.hpp"
#include "../expr/Expression.hpp"

#include <cstdlib>

void *PParseAlloc(void *(*mallocProc)(size_t));
void PParseFree(void *p, void (*freeProc)(void*));
void PParse(void *yyp, int yymajor, Token yyminor, Expression * * root);
void PParseTrace(FILE * stream, char * zPrefix);

class Parser
  : public Object
  , public PScanner_Callback
{
public:
  Parser()
    : scanner_()
    , parser_(PParseAlloc(std::malloc))
    , root_()
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

  // TODO: calling parse_stream multiple times will overwrite root_
  // (solution: parse_stream should return root expression, but at the
  // moment this requires refactoring)
  Expression * root() const { return root_; }

protected:
  virtual void have_token(int id, Token const & token)
  {
    PParse(parser_, id, token, &root_);
  }

private:
  PScanner scanner_;
  void * parser_;
  Expression * root_;
};

#endif // PARSER__HPP

