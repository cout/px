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
      std::string const & slot,
      Expression * receiver,
      Expression * message)
    : slot(new String(slot))
    , receiver(receiver)
    , message(message)
  {
  }

  Send(
      Ref<Object> slot,
      Expression * receiver,
      Expression * message)
    : slot(slot)
    , receiver(receiver)
    , message(message)
  {
  }

  Ref<Object> slot;
  Ref<Expression> receiver;
  Ref<Expression> message;

  virtual std::string to_string() const {
    return std::string(
        receiver->to_string() +
        std::string(".") +
        slot->to_string() +
        "(" + message->to_string() + ")");
  }

  virtual Ref<Object> eval(Ref<Context> context)
  {
    Ref<Object> recv = receiver->eval(context);
    Ref<Object> attr = recv->getattr(slot);
    return attr->receive(message, context);
  }
};

#endif
