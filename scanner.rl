#include "scanner.hpp"
#include "p.hpp"

#include <stdexcept>
#include <cstring>
#include <iostream>

%%{
  machine p_lexer;

  integer = [0-9];
  float = [0-9]+|[0-9]*.[0-9]+;
  string = "\""[^"]*"\"";
  identifier = ([A-Z][a-z])([A-Z][a-z][0-9])*;

  main := |*
    "\n"       => { return PTOKEN_NEWLINE;     } ;
    ";"        => { return PTOKEN_SEMICOLON;   } ;
    "="        => { return PTOKEN_ASSIGN;      } ;
    ","        => { return PTOKEN_COMMA;       } ;
    ":"        => { return PTOKEN_COLON;       } ;
    "&"        => { return PTOKEN_AND;         } ;
    "|"        => { return PTOKEN_OR;          } ;
    "=="       => { return PTOKEN_EQ;          } ;
    "!="       => { return PTOKEN_NE;          } ;
    ">"        => { return PTOKEN_GT;          } ;
    ">="       => { return PTOKEN_GE;          } ;
    "<"        => { return PTOKEN_LT;          } ;
    "<="       => { return PTOKEN_LE;          } ;
    "+"        => { return PTOKEN_PLUS;        } ;
    "-"        => { return PTOKEN_MINUS;       } ;
    "/"        => { return PTOKEN_DIVIDE;      } ;
    "*"        => { return PTOKEN_TIMES;       } ;
    "%"        => { return PTOKEN_MOD;         } ;
    "^"        => { return PTOKEN_EXP;         } ;
    "!"        => { return PTOKEN_NOT;         } ;
    "("        => { return PTOKEN_LPAREN;      } ;
    ")"        => { return PTOKEN_RPAREN;      } ;
    "{"        => { return PTOKEN_LBRACE;      } ;
    "}"        => { return PTOKEN_RBRACE;      } ;
    integer    => { 
      // token_.ival = boost::lexical_cast<long>(yytext);
      return PTOKEN_INTEGER;
    };
    float      => {
      // token_.dval = boost::lexical_cast<double>(yytext);
      return PTOKEN_FLOAT;
    };
    string     => {
      // token_.sval = yytext;
      return PTOKEN_STRING;
    };
    identifier => {
      // token_.sval = yytext;
      return PTOKEN_IDENTIFIER;
    };
  *|;
}%%

%% write data;

PScanner::
PScanner()
  : token_()
  , have_(0)
{
  %% write init;
}

size_t
PScanner::
buffer_space_remaining(size_t bufsize, size_t have)
{
  // How much space is in the buffer?
  size_t space = bufsize - have;
  if ( space == 0 ) {
    throw std::runtime_error("Token too big");
  }

  return space;
}

void
PScanner::
check_for_error()
{
  if ( cs < %%{ write first_final; }%% ) {
    throw std::runtime_error("Parse error");
  }
}

void
PScanner::
check_for_fragments(char const * p, char const * pe)
{
  if ( ts == 0 )
    have_ = 0;
  else {
    /* There is a prefix to preserve, shift it over. */
    have_ = pe - ts;
    std::memmove( inbuf_, ts, have_ );
    te = inbuf_ + (te-ts);
    ts = inbuf_;
  }
}

int
PScanner::
scan_stream(std::istream & in)
{
  bool done = false;
  while ( !done ) {
    size_t space = buffer_space_remaining(BUFSIZE, have_);

    // Read in a block.
    char *p = inbuf_ + have_; // Ragel: current character position
    in.read( p, space );
    int len = in.gcount();
    char *pe = p + len; // Ragel: pointer to buffer end
    char *eof = 0;

    // Check for EOF.
    if ( len == 0 ) {
      eof = pe;
      done = true;
    }

    %% write exec;

    check_for_error();
    check_for_fragments(p, pe);
  }
  return 0;
}
