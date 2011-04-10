%include {
#include <iostream>
#include <stdexcept>
#include <cassert>
#include "p.hpp"
#include "Token.hpp"
}

%token_type { Token }
%default_type { Token }
%name PParse
%token_prefix PTOKEN_

%type expr { Token }

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

program ::= expr.

/* Arithmetic operators */
expr ::= arith.
arith ::= expr MINUS expr.
arith ::= expr PLUS expr.
arith ::= expr TIMES expr.
arith ::= expr DIVIDE expr.
arith ::= expr MOD expr.
arith ::= expr EXP expr.

/* Logical operators */
expr ::= logic.
logic ::= expr EQ expr.
logic ::= expr NE expr.
logic ::= expr GT expr.
logic ::= expr GE expr.
logic ::= expr LT expr.
logic ::= expr LE expr.
logic ::= NOT expr.

/* Literals */
expr ::= literal.
literal ::= INTEGER|FLOAT|STRING.

/* Tuples */
expr ::= tuple.
tuple ::= LPAREN expr RPAREN.

/* Comma operator */
expr ::= expr COMMA expr.

/* Function calls */
/* TODO: keyword arguments */
expr ::= funcall.
funcall ::= expr tuple.
funcall ::= expr tuple block.

/* Blocks */
expr ::= block.
block ::= LBRACE expr RBRACE.

/* Statements */
expr ::= expr NEWLINE expr.
expr ::= expr SEMICOLON expr.

/* Pairs */
expr ::= pair.
pair ::= expr COLON expr.

/* Assignment */
expr ::= assignment.
assignment ::= IDENTIFIER ASSIGN expr.

