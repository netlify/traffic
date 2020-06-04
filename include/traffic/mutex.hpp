#ifndef TRAFFIC_MUTEX_HPP
#define TRAFFIC_MUTEX_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSMutex> {
  using pointer = TSMutex;
  void operator () (pointer ptr) const noexcept;
};

// This is an *owned* mutex handle. If you need to 'borrow' or use
// a continuations mutex, just use std::lock directly on the type, as they
// each meet the lockable named requirement
struct mutex : protected unique_handle<TSMutex> {
  using native_handle_type = TSMutex;

  mutex (mutex const&) = delete;
  mutex& operator = (mutex const&) = delete;

  mutex (native_handle_type) noexcept;
  mutex () noexcept;

  bool try_lock () noexcept;
  void unlock () noexcept;
  void lock () noexcept;

  native_handle_type native_handle () const noexcept;

private:
  native_handle_type handle;
};

} /* namespace traffic */

#endif /* TRAFFIC_MUTEX_HPP */
