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
{
}

int
PScanner::
p_scan(std::istream & in)
{
  int cs, act;
  char *ts, *te;
  int stack[1], top;

  size_t const BUFSIZE = 1024;
  static char inbuf[BUFSIZE];
  bool single_line = false;
  int inline_depth = 0;

  %% write init;

  bool done = false;
  int have = 0;
  while ( !done ) {
    /* How much space is in the buffer? */
    int space = BUFSIZE - have;
    if ( space == 0 ) {
      throw std::runtime_error("Token too big");
    }

    /* Read in a block. */
    char *p = inbuf + have;
    in.read( p, space );
    int len = in.gcount();
    char *pe = p + len;
    char *eof = 0;

    /* Check for EOF. */
    if ( len == 0 ) {
      eof = pe;
      done = true;
    }

    %% write exec;

/*
    if ( cs == RagelScan_error ) {
      throw std::runtime_error("Parse error");
    }
*/

    if ( ts == 0 )
      have = 0;
    else {
      /* There is a prefix to preserve, shift it over. */
      have = pe - ts;
      std::memmove( inbuf, ts, have );
      te = inbuf + (te-ts);
      ts = inbuf;
    }
  }
  return 0;
}
