#include "Function.hpp"

Ref<Object>
Function::
receive(Ref<Object> msg, Ref<Context> context)
{
  return this->call(msg->eval(context), context);
}

