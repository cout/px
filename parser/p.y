%include {
#include "ast.hpp"
#include "p.hpp"
#include "Token.hpp"
#include "../object/Integer.hpp"
#include "../object/Float.hpp"
#include "../object/String.hpp"

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

%destructor expr { delete $$; }

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
%right LPAREN.
%left RPAREN.

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
logic(RESULT) ::= NOT expr(EXPR).         { RESULT = new Send("not", EXPR, new Null); }

/* Literals */
expr(RESULT) ::= literal(LITERAL). { RESULT = LITERAL; }
literal(RESULT) ::= INTEGER. { RESULT = new Literal(new Integer(0)); /* TODO */}
literal(RESULT) ::= FLOAT. { RESULT = new Literal(new Float(0.0)); /* TODO */}
literal(RESULT) ::= STRING. { RESULT = new Literal(new String("")); /* TODO */}

/* Tuples */
expr(RESULT) ::= tuple(TUPLE). { RESULT = TUPLE; }
tuple(RESULT) ::= LPAREN expr(EXPR) RPAREN. { RESULT = new Send("tuple", EXPR, new Null); }

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

/* Pairs */
expr(RESULT) ::= pair(PAIR). { RESULT = PAIR; }
pair(RESULT) ::= expr(LHS) COLON expr(RHS). { RESULT = new Send("colon", LHS, RHS); }

/* Assignment */
expr(RESULT) ::= assignment(ASSGN). { RESULT = ASSGN; }
assignment(RESULT) ::= IDENTIFIER ASSIGN expr. { RESULT = new Assign; }

