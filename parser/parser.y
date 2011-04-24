%include {
#include "parser.hpp"
#include "Token.hpp"

#include "../object/Integer.hpp"
#include "../object/Float.hpp"
#include "../object/String.hpp"
#include "../object/Nil.hpp"

#include "../expr/Block.hpp"
#include "../expr/Expression.hpp"
#include "../expr/Send.hpp"

#include <iostream>
#include <stdexcept>

#include <iostream>
#include <stdexcept>
#include <cassert>
}

%token_type { Token }
%name PParse
%token_prefix PTOKEN_

%start_symbol program
%type expr { Expression * }
%default_type { Expression * }

/* %destructor expr { delete $$; } */

%extra_argument { Expression * * root }

%parse_failure {
  throw std::runtime_error("parse failure");
}

%stack_overflow {
  throw std::runtime_error("stack overflow");
}

/* TODO: precedence and associativity of parens/braces? */
%left NEWLINE SEMICOLON.
%left ASSIGN.
%left COMMA.
%left COLON.
%left AND.
%left OR.
%left EQ NE GT GE LT LE. /* TODO: should be nonassoc */
%left PLUS MINUS.
%left DIVIDE TIMES MOD.
%right EXP NOT.
%right LPAREN LBRACKET.
%left RPAREN RBRACKET.
%left DOT.

%syntax_error {
throw std::runtime_error("Syntax error");
}

program ::= expr(EXPR). { *root = EXPR; }

/* Arithmetic operators */
expr(RESULT) ::= arith(ARITH). { RESULT = ARITH; }
arith(RESULT) ::= expr(LHS) MINUS expr(RHS).  { RESULT = new Send("minus", LHS, RHS); }
arith(RESULT) ::= expr(LHS) PLUS expr(RHS).   { RESULT = new Send("plus", LHS, RHS);  }
arith(RESULT) ::= expr(LHS) TIMES expr(RHS).  { RESULT = new Send("times", LHS, RHS); }
arith(RESULT) ::= expr(LHS) DIVIDE expr(RHS). { RESULT = new Send("div", LHS, RHS);   }
arith(RESULT) ::= expr(LHS) MOD expr(RHS).    { RESULT = new Send("mod", LHS, RHS);   }
arith(RESULT) ::= expr(LHS) EXP expr(RHS).    { RESULT = new Send("exp", LHS, RHS);   }

/* Logical operators */
expr(RESULT) ::= logic(LOGIC). { RESULT = LOGIC; }
logic(RESULT) ::= expr(LHS) EQ expr(RHS). { RESULT = new Send("eq", LHS, RHS); }
logic(RESULT) ::= expr(LHS) NE expr(RHS). { RESULT = new Send("ne", LHS, RHS); }
logic(RESULT) ::= expr(LHS) GT expr(RHS). { RESULT = new Send("gt", LHS, RHS); }
logic(RESULT) ::= expr(LHS) GE expr(RHS). { RESULT = new Send("ge", LHS, RHS); }
logic(RESULT) ::= expr(LHS) LT expr(RHS). { RESULT = new Send("lt", LHS, RHS); }
logic(RESULT) ::= expr(LHS) LE expr(RHS). { RESULT = new Send("le", LHS, RHS); }
logic(RESULT) ::= NOT expr(EXPR).         { RESULT = new Send("not", EXPR, Nil.get()); }

/* Literals */
expr(RESULT) ::= literal(LITERAL). { RESULT = LITERAL; }
literal(RESULT) ::= INTEGER(VALUE). { RESULT = new Integer(VALUE.ival); }
literal(RESULT) ::= FLOAT(VALUE). { RESULT = new Float(VALUE.dval); }
literal(RESULT) ::= STRING(VALUE). { RESULT = new String(VALUE.ts, VALUE.te); }

/* Tuples */
expr(RESULT) ::= tuple(TUPLE). { RESULT = TUPLE; }
tuple(RESULT) ::= LPAREN expr(EXPR) RPAREN. { RESULT = new Send("tuple", EXPR, Nil.get()); }

/* Comma operator */
expr(RESULT) ::= list(LIST). { RESULT = LIST; }
list(RESULT) ::= expr(LHS) COMMA expr(RHS). { RESULT = new Send("comma", LHS, RHS); }

/* Function calls */
/* TODO: keyword arguments */
expr(RESULT) ::= funcall(FUNCALL). { RESULT = FUNCALL; }
funcall(RESULT) ::= expr(RECV) tuple(ARGS). { RESULT = new Send("call", RECV, ARGS); }
funcall(RESULT) ::= expr(RECV) tuple(ARGS) block(BLOCK). {
  Expression * args = new Send("comma", ARGS, BLOCK);
  RESULT = new Send("call", RECV, args);
}

/* Blocks */
expr(RESULT) ::= block(BLOCK). { RESULT = BLOCK; }
block(RESULT) ::= LBRACE expr(EXPR) RBRACE. { RESULT = new Block(EXPR); }
expr(RESULT) ::= expr(LHS) NEWLINE expr(RHS). { RESULT = new Send("newline", LHS, RHS); }
expr(RESULT) ::= expr(LHS) SEMICOLON expr(RHS). { RESULT = new Send("semicolon", LHS, RHS); }
expr(RESULT) ::= expr(LHS) NEWLINE. { RESULT = LHS; }
expr(RESULT) ::= expr(LHS) SEMICOLON. { RESULT = LHS; }
expr(RESULT) ::= NEWLINE expr(RHS). { RESULT = RHS; }
expr(RESULT) ::= SEMICOLON expr(RHS). { RESULT = RHS; }

/* Attributes */
expr(RESULT) ::= getattr(GETATTR). { RESULT = GETATTR; }
getattr(RESULT) ::= expr(RECV) LBRACKET expr(KEY) RBRACKET.
{
  RESULT = new Send("get", RECV, KEY);
}

expr(RESULT) ::= setattr(SETATTR). { RESULT = SETATTR; }
setattr(RESULT) ::= expr(RECV) LBRACKET expr(KEY) RBRACKET ASSIGN expr(VALUE).
{
  Ref<Object> pair = new Send("colon", KEY, VALUE);
  RESULT = new Send("set", RECV, pair);
}

expr(RESULT) ::= dotaccess(DOTACCESS). { RESULT = DOTACCESS; }
dotaccess(RESULT) ::= expr(RECV) DOT IDENTIFIER(ID). {
  Ref<String> id = new String(ID.ts, ID.te);
  RESULT = new Send("get", RECV, id);
}

/* Pairs */
expr(RESULT) ::= pair(PAIR). { RESULT = PAIR; }
pair(RESULT) ::= expr(LHS) COLON expr(RHS). { RESULT = new Send("colon", LHS, RHS); }

/* Locals */
expr(RESULT) ::= IDENTIFIER(ID).
{
  Ref<String> id = new String(ID.ts, ID.te);
  RESULT = new Send("local_get", id, Nil);
}
expr(RESULT) ::= IDENTIFIER(ID) ASSIGN expr(VALUE).
{
  Ref<String> id = new String(ID.ts, ID.te);
  RESULT = new Send("local_set", id, VALUE);
}

/* vim: set ft=cpp: */
