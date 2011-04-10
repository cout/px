#ifndef LEXGLOBAL__HPP_

#ifndef YYSTYPE
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

struct YYSTYPE {
  long        ival;
  double      dval;
  std::string sval;
};

extern YYSTYPE yylval;

#endif // LEXGLOBAL__HPP_

