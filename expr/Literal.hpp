#ifndef LITERAL__HPP
#define LITERAL__HPP

class Literal
  : public Expression
{
public:
  Literal(Ref<Object> value) : value(value) { }

  virtual std::string to_string() const { return "LITERAL"; }
  virtual Ref<Object> eval() { return Nil; }

  Ref<Object> value;
};

#endif

