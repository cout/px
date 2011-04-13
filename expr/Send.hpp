#ifndef SEND__HPP
#define SEND__HPP

#include "Expression.hpp"

#include <stdexcept>
#include <sstream>
#include <string>

class Send
  : public Expression
{
public:
  Send(
      std::string const & name,
      Expression * receiver,
      Expression * message)
    : name(new String(name))
    , receiver(receiver)
    , message(message)
  {
  }

  Send(
      Ref<Object> name,
      Expression * receiver,
      Expression * message)
    : name(name)
    , receiver(receiver)
    , message(message)
  {
  }

  Ref<Object> name;
  Ref<Expression> receiver;
  Ref<Expression> message;

  virtual std::string to_string() const {
    return std::string(
        receiver->to_string() +
        std::string(".") +
        name->to_string() +
        "(" + message->to_string() + ")");
  }

  virtual Ref<Object> eval(Ref<Context> context)
  {
    Ref<Object> recv = receiver->eval(context);

    return recv->receive(name, message, context);
  }
};

#endif
