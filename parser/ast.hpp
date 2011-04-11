#ifndef AST__HPP
#define AST__HPP

#include "../object/Object.hpp"

#include <string>

class Expression
  : public Object
{
public:
  virtual ~Expression() { }

  virtual std::string to_string() const = 0;
};

class Null
  : public Expression
{
  virtual std::string to_string() const { return "()"; }
};

class Block
  : public Expression
{
public:
  Block(Expression * next) : next(next) { }

  Ref<Expression> next;

  virtual std::string to_string() const { return std::string("{") + next->to_string() + "}"; }
};

class Send
  : public Expression
{
public:
  Send(
      std::string name,
      Expression * receiver,
      Expression * message)
    : name(name)
    , receiver(receiver)
    , message(message)
  {
  }

  std::string name;
  Ref<Expression> receiver;
  Ref<Expression> message;

  virtual std::string to_string() const { return receiver->to_string() + "." + name + message->to_string(); }
};

class Assign
  : public Expression
{
public:
  std::string slot;
  Ref<Expression> value;

  virtual std::string to_string() const { return slot + "=" + value->to_string(); }
};

class Literal
  : public Expression
{
public:
  Literal(Ref<Object> value) : value(value) { }

  virtual std::string to_string() const { return "LITERAL"; }

  Ref<Object> value;
};

#endif // AST__HPP