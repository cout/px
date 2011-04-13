#ifndef OBJECT__HPP
#define OBJECT__HPP

#include "Ref.hpp"

#include <map>
#include <stdexcept>
#include <sstream>

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

  virtual Ref<Object> getattr(Ref<Object> attr) {
    Slots::iterator it(slots.find(attr));
    if (it == slots.end())
    {
      std::stringstream strm;
      strm << "No such slot " << attr->to_string() << " in " << this->to_string();
      throw std::runtime_error(strm.str());
    }
    return it->second;
  }

  virtual bool operator<(Object const & rhs) const
  {
    return this < &rhs;
  }
};

#endif

