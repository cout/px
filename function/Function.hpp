#ifndef FUNCTION__HPP
#define FUNCTION__HPP

#include "../object/Object.hpp"

class Function
  : public Object
{
public:
  Function();

  static Ref<Object> make_prototype();

  virtual Ref<Object> receive(Ref<Object> recv, Ref<Object> msg, Ref<Context> context);

  virtual Ref<Object> call(Ref<Object> recv, Ref<Object> msg, Ref<Context> context) = 0;
};

#endif
 
