#ifndef REF__HPP
#define REF__HPP

template<typename Object_T>
class Ref
{
public:
  Ref() : ptr(0) { }
  Ref(Object_T * ptr) : ptr(ptr) { }

  Object_T & operator*() { return *ptr; }
  Object_T * operator->() { return ptr; }

  Object_T const & operator*() const { return *ptr; }
  Object_T const * operator->() const { return ptr; }

  Object_T * ptr;
};

#endif

