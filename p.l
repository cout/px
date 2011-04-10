%{
#include <cstring>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include "p.hpp"
#include "lexglobal.hpp"

YYSTYPE yylval;

void scanner_error(char const * s)
{
  char buf[1024];
  std::snprintf(buf, sizeof(buf), "Error: %s", s);
}


%}

%option warn
%option yylineno
%option outfile="scanner.cpp"

%%

"\n"          { return PTOKEN_NEWLINE;     } 
";"           { return PTOKEN_SEMICOLON;   } 
"="           { return PTOKEN_ASSIGN;      } 
","           { return PTOKEN_COMMA;       } 
":"           { return PTOKEN_COLON;       } 
"&"           { return PTOKEN_AND;         } 
"|"           { return PTOKEN_OR;          } 
"=="          { return PTOKEN_EQ;          } 
"!="          { return PTOKEN_NE;          } 
">"           { return PTOKEN_GT;          } 
">="          { return PTOKEN_GE;          } 
"<"           { return PTOKEN_LT;          } 
"<="          { return PTOKEN_LE;          } 
"+"           { return PTOKEN_PLUS;        } 
"-"           { return PTOKEN_MINUS;       } 
"/"           { return PTOKEN_DIVIDE;      } 
"*"           { return PTOKEN_TIMES;       } 
"%"           { return PTOKEN_MOD;         } 
"^"           { return PTOKEN_EXP;         } 
"!"           { return PTOKEN_NOT;         } 
"("           { return PTOKEN_LPAREN;      } 
")"           { return PTOKEN_RPAREN;      } 
"{"           { return PTOKEN_LBRACE;      } 
"}"           { return PTOKEN_RBRACE;      } 

[0-9] {
  yylval.ival = boost::lexical_cast<long>(yytext);
  return PTOKEN_INTEGER;
}

[0-9]+|[0-9]*.[0-9]+ {
  yylval.dval = boost::lexical_cast<double>(yytext);
  return PTOKEN_FLOAT;
} 

([A-Z][a-z])([A-Z][a-z][0-9])* {
  yylval.sval = yytext;
  return PTOKEN_IDENTIFIER;
} 

"\""[^"]*"\"" {
  yylval.sval = yytext;
  return PTOKEN_STRING;
} 

%%

void reset_lexer()
{
}

void yyerror(char * s)
{
  scanner_error(s);
}

int yyFlexLexer::yywrap()
{
  return 1;
}

