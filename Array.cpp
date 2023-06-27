#include "Array.hpp"
#include "VulkanErrors.hpp"

namespace Sol {
#if 0

template<typename T>
void Array<T>::init(size_t size, size_t alignment) {
  cap = size;
  mem = (T*)mem_alloc2(size * sizeof(T), alignment, alloc);
}
template<typename T>
void Array<T>::reset() {
  len = 0;
}

template<typename T>
void Array<T>::push(T t) {
  ABORT(len != cap, "Push to Array<T> with insufficient");
  mem[len] = t;
  ++len;
}
template<typename T>
T Array<T>::pop() {
  --len;
  return mem[len];
}
template<typename T>
void Array<T>::swap_last(size_t i) {
  ABORT(i < len, "Out of bounds access on Array<T>");
  T tmp = mem[i];
  mem[i] = mem[len - 1];
  mem[len - 1] = tmp;
}
template<typename T>
void Array<T>::copy_here(T* data, size_t count) {
  ABORT(cap - len > count, "Array<T>::copy_here with insufficient size");
  mem_cpy(mem + len, data, count * sizeof(T));
  len += count;
}

template<typename T>
T& Array<T>::operator[](size_t i) {
  ABORT(i < len, "Out of Bounds access on Array<T>");
  return mem[i];
}
#endif

} // namespace Sol 
