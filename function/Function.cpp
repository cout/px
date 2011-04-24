#include "Function.hpp"

Ref<Object>
Function::
receive(Ref<Object> recv, Ref<Object> msg, Ref<Context> context)
{
  return this->call(recv, msg->eval(context), context);
}

