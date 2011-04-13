#ifndef OBJECT_DEFN__HPP
#define OBJECT_DEFN__HPP

#include "Ref.hpp"

#include <map>
#include <stdexcept>

class Context;

class Object
{
public:
  virtual std::string to_string() const = 0;

  typedef std::map<Ref<Object>, Ref<Object> > Slots;
  Slots slots;

  virtual Ref<Object> eval(Ref<Context> /* context */) { return Ref<Object>(this); }

  virtual Ref<Object> receive(
      Ref<Object> /* msg */,
      Ref<Context> /* context */)
  {
    throw std::runtime_error("Object cannot receive messages");
  }

  virtual Ref<Object> getattr(Ref<Object> attr);

  virtual bool operator<(Object const & rhs) const
  {
    return this < &rhs;
  }
};

#endif

