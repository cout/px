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
      Ref<Expression> receiver,
      Ref<Expression> message)
    : slot(new String(slot))
    , receiver(receiver)
    , message(message)
  {
  }

  Send(
      Ref<Object> slot,
      Ref<Expression> receiver,
      Ref<Expression> message)
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
    std::cout << "SLOT: " << slot->to_string() << std::endl;
    Ref<Object> recv = receiver->eval(context);
    std::cout << "RECV: " << recv->to_string() << std::endl;
    Ref<Object> attr = recv->getattr(slot);
    std::cout << "ATTR: " << attr->to_string() << std::endl;
    return attr->receive(recv, message, context);
  }
};

#endif
