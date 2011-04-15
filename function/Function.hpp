#ifndef FUNCTION__HPP
#define FUNCTION__HPP

#include "../object/Object.hpp"

class Function
  : public Object
{
public:
  Function() { }

  virtual Ref<Object> receive(
      Ref<Object> name,
      Ref<Expression> msg,
      Ref<Context> context);

  virtual Ref<Object> call(Ref<Object> msg) = 0;
};

#endif
 
