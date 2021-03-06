#include "scanner.hpp"
#include "parser.hpp"

#include <boost/lexical_cast.hpp>
#
#include <stdexcept>
#include <cstring>
#include <iostream>

%%{
  machine p_lexer;

  integer = [0-9];
  float = [0-9]+|[0-9]*.[0-9]+;
  quote = "\"";
  string = quote [^"]* quote;
  identifier = ([A-Z]|[a-z])([A-Z]|[a-z]|[0-9])*;

  main := |*
    [ \t]      => { } ;
    "\n"       => { cb.have_token(PTOKEN_NEWLINE, token);   } ;
    ";"        => { cb.have_token(PTOKEN_SEMICOLON, token); } ;
    "="        => { cb.have_token(PTOKEN_ASSIGN, token);    } ;
    ","        => { cb.have_token(PTOKEN_COMMA, token);     } ;
    ":"        => { cb.have_token(PTOKEN_COLON, token);     } ;
    "&"        => { cb.have_token(PTOKEN_AND, token);       } ;
    "|"        => { cb.have_token(PTOKEN_OR, token);        } ;
    "=="       => { cb.have_token(PTOKEN_EQ, token);        } ;
    "!="       => { cb.have_token(PTOKEN_NE, token);        } ;
    ">"        => { cb.have_token(PTOKEN_GT, token);        } ;
    ">="       => { cb.have_token(PTOKEN_GE, token);        } ;
    "<"        => { cb.have_token(PTOKEN_LT, token);        } ;
    "<="       => { cb.have_token(PTOKEN_LE, token);        } ;
    "+"        => { cb.have_token(PTOKEN_PLUS, token);      } ;
    "-"        => { cb.have_token(PTOKEN_MINUS, token);     } ;
    "/"        => { cb.have_token(PTOKEN_DIVIDE, token);    } ;
    "*"        => { cb.have_token(PTOKEN_TIMES, token);     } ;
    "%"        => { cb.have_token(PTOKEN_MOD, token);       } ;
    "^"        => { cb.have_token(PTOKEN_EXP, token);       } ;
    "!"        => { cb.have_token(PTOKEN_NOT, token);       } ;
    "("        => { cb.have_token(PTOKEN_LPAREN, token);    } ;
    ")"        => { cb.have_token(PTOKEN_RPAREN, token);    } ;
    "{"        => { cb.have_token(PTOKEN_LBRACE, token);    } ;
    "}"        => { cb.have_token(PTOKEN_RBRACE, token);    } ;
    "["        => { cb.have_token(PTOKEN_LBRACKET, token);  } ;
    "]"        => { cb.have_token(PTOKEN_RBRACKET, token);  } ;
    integer    => { 
      token.ival = boost::lexical_cast<long>(std::string(ts, te));
      cb.have_token(PTOKEN_INTEGER, token);
    };
    float      => {
      token.dval = boost::lexical_cast<double>(std::string(ts, te));
      cb.have_token(PTOKEN_FLOAT, token);
    };
    string     => {
      token.ts = ts;
      token.te = te;
      cb.have_token(PTOKEN_STRING, token);
    };
    identifier => {
      token.ts = ts;
      token.te = te;
      cb.have_token(PTOKEN_IDENTIFIER, token);
    };
  *|;
}%%

%% write data;

PScanner::
PScanner()
  : have_(0)
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
check_for_error(char const * p, char const * pe)
{
  if ( cs < %%{ write first_final; }%% ) {
    std::stringstream strm;
    strm << "Error during scanning:" << std::endl
         << std::string(p, pe) << std::endl;
         // << std::string(ts, te);
    throw std::runtime_error(strm.str());
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

void
PScanner::
scan_stream(std::istream & in, PScanner_Callback & cb)
{
  Token token;

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

    check_for_error(p, pe);
    check_for_fragments(p, pe);
  }

  cb.have_token(0, token);
}
