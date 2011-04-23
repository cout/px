#ifndef OBJECT_DEFN__HPP
#define OBJECT_DEFN__HPP

#include "Ref.hpp"

#include "../expr/Expression.hpp"

#include <map>
#include <stdexcept>

class Context;

class Object
{
public:
  virtual std::string to_string() const = 0;

  typedef std::map<Ref<Object>, Ref<Object> > Slots;
  Slots slots;

  Ref<Object> prototype;

  Object();

  Object(Ref<Object> prototype);

  static Ref<Object> make_prototype();

  virtual ~Object() { }

  virtual Ref<Object> eval(
      Ref<Context> context);

  virtual Ref<Object> receive(
      Ref<Expression> msg,
      Ref<Context> context);

  virtual Ref<Object> getattr(
      Ref<Object> name);

  virtual Ref<Object> getattr(
      char const * name);

  virtual void setattr(
      Ref<Object> name,
      Ref<Object> value);

  virtual void setattr(
      char const * name,
      Ref<Object> value);

  virtual bool operator<(Object const & rhs) const
  {
    return this < &rhs;
  }

  virtual bool operator==(Object const & rhs) const
  {
    return this == &rhs;
  }

  virtual bool is_defined() const { return true; }
};

#endif

