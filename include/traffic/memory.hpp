#ifndef TRAFFIC_MEMORY_HPP
#define TRAFFIC_MEMORY_HPP

#include <apex/mixin/handle.hpp>
#include <apex/memory/retain.hpp>
#include <apex/memory/view.hpp>
#include <apex/core/source.hpp>
#include <apex/core/traits.hpp>
#include <cstddef>
#include <memory>

namespace traffic {

// This will only ever be specialized. It won't be  sitting out on its own.
template <class T>
struct default_delete {
  void operator () (T* ptr) const noexcept = delete;
};

template <class T>
struct retain_traits {
  static void increment (T* ptr) noexcept;
  static void decrement (T* ptr) noexcept;
};

struct track_t { };
inline constexpr track_t track { };

template <class T, class D=default_delete<T>>
using unique_ptr = std::unique_ptr<T, D>;

template <class T, class D=default_delete<T>>
using unique_handle = apex::mixin::handle<T, unique_ptr<T, D>>;

template <class T, class R=retain_traits<T>>
using retain_handle = apex::mixin::handle<T, apex::retain_ptr<T, R>>;

template <class T>
using view_handle = apex::mixin::handle<
  std::remove_pointer_t<T>,
  apex::view_ptr<std::remove_pointer_t<T>>
>;

} /* namespace traffic */

// TODO: Replace with {apex|std}::source_location when possible. That said,
// this works with Clang 10 and GCC.
// This replaces using TSmalloc directly
void* operator new (
  std::size_t,
  traffic::track_t,
  apex::source_location = apex::source_location::current()) noexcept;

// Required to be defined, but only called if new throws, which ours does not
void operator delete (
  void*,
  traffic::track_t,
  apex::source_location = apex::source_location::current()) noexcept;

#endif /* TRAFFIC_MEMORY_HPP */
