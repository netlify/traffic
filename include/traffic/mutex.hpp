#ifndef TRAFFIC_MUTEX_HPP
#define TRAFFIC_MUTEX_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSMutex> {
  using pointer = TSMutex;
  void operator () (pointer ptr) const noexcept;
};

/* This is an *owned* mutex handle. A borrowed_mutex type is available,
 * however it will be removed once all mutex-capable types are properly wrapped
 * (TSCont, TSVConn, etc.). A release applying [[deprecated]] will be performed
 * before this removal, however.
 */
struct [[clang::capability("mutex")]] mutex : protected unique_handle<TSMutex> {
  using native_handle_type = TSMutex;

  using resource_type::resource_type;
  using resource_type::operator bool;

  mutex () noexcept;

  [[clang::try_acquire_capability(true)]] bool try_lock () noexcept;
  [[clang::release_capability]] void unlock () noexcept;
  [[clang::acquire_capability]] void lock () noexcept;

  native_handle_type native_handle () const noexcept;
};

struct [[clang::capability("mutex")]] borrowed_mutex : protected view_handle<TSMutex> {
  using native_handle_type = TSMutex;

  borrowed_mutex (TSCont cont) noexcept;

  borrowed_mutex& operator = (borrowed_mutex const&) = delete;
  borrowed_mutex (borrowed_mutex const&) = delete;

  using resource_type::resource_type;
  using resource_type::operator bool;

  [[clang::try_acquire_capability(true)]] bool try_lock () noexcept;
  [[clang::release_capability]] void unlock () noexcept;
  [[clang::acquire_capability]] void lock () noexcept;

  native_handle_type native_handle () const noexcept;
};

} /* namespace traffic */

#endif /* TRAFFIC_MUTEX_HPP */
