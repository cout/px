%{
#include <cstring>
#include <stdexcept>

#include "p.hpp"
%}

%%

"\n"                              { return PTOKEN_NEWLINE;     } 
";"                               { return PTOKEN_SEMICOLON;   } 
"="                               { return PTOKEN_ASSIGN;      } 
","                               { return PTOKEN_COMMA;       } 
":"                               { return PTOKEN_COLON;       } 
"&"                               { return PTOKEN_AND;         } 
"|"                               { return PTOKEN_OR;          } 
"=="                              { return PTOKEN_EQ;          } 
"!="                              { return PTOKEN_NE;          } 
">"                               { return PTOKEN_GT;          } 
">="                              { return PTOKEN_GE;          } 
"<"                               { return PTOKEN_LT;          } 
"<="                              { return PTOKEN_LE;          } 
"+"                               { return PTOKEN_PLUS;        } 
"-"                               { return PTOKEN_MINUS;       } 
"/"                               { return PTOKEN_DIVIDE;      } 
"*"                               { return PTOKEN_TIMES;       } 
"%"                               { return PTOKEN_MOD;         } 
"^"                               { return PTOKEN_EXP;         } 
"!"                               { return PTOKEN_NOT;         } 
"("                               { return PTOKEN_LPAREN;      } 
")"                               { return PTOKEN_RPAREN;      } 
[0-9]                             { return PTOKEN_INTEGER;     } 
[0-9]+|[0-9]*.[0-9]+              { return PTOKEN_FLOAT;       } 
"\""[^"]*"\""                     { return PTOKEN_STRING;      } 
"{"                               { return PTOKEN_LBRACE;      } 
"}"                               { return PTOKEN_RBRACE;      } 
([A-Z][a-z])([A-Z][a-z][0-9])*    { return PTOKEN_IDENTIFIER;  } 

%%

void reset_lexer()
{
}

void yyerror(char * s)
{
  char buf[1024];
  std::snprintf(buf, sizeof(buf), "Error: %s" % s);
  throw std::runtime_error(buf);
}

int yywrap()
{
  return 1;
}

