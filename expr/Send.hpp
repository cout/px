#ifndef SEND__HPP
#define SEND__HPP

#include "Expression.hpp"

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
  virtual Ref<Object> eval() { return Nil; }
};

#endif
