#ifndef REF__HPP
#define REF__HPP

template<typename Object_T>
class Ref
{
public:
  Ref() : ptr(0) { }
  Ref(Object_T * ptr) : ptr(ptr) { }

  template<typename T>
  Ref(Ref<T> ref) : ptr(ref.ptr) { }

  Object_T & operator*() { return *ptr; }
  Object_T * operator->() { return ptr; }
  Object_T * get() { return ptr; }

  Object_T const & operator*() const { return *ptr; }
  Object_T const * operator->() const { return ptr; }
  Object_T * get() const { return ptr; }

  Object_T * ptr;

  template<typename T>
  bool operator<(Ref<T> const & rhs) const
  {
    return *ptr < *rhs;
  }
};

#endif

