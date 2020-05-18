#ifndef TRAFFIC_MUTEX_HPP
#define TRAFFIC_MUTEX_HPP

#include <ts/ts.h>

namespace traffic {

// This is an *owned* mutex handle. If you need to 'borrow' or use
// a continuations mutex, just use std::lock directly on the type, as they
// each meet the lockable named requirement
struct mutex {
  using native_handle_type = TSMutex;

  mutex (mutex const&) = delete;
  mutex& operator = (mutex const&) = delete;

  mutex (native_handle_type) noexcept;
  mutex () noexcept;
  ~mutex () noexcept;

  explicit operator bool () const noexcept;

  bool try_lock () noexcept;
  void unlock () noexcept;
  void lock () noexcept;

  native_handle_type native_handle () const noexcept;
  native_handle_type get () const noexcept;

private:
  native_handle_type handle;
};

} /* namespace traffic */

#endif /* TRAFFIC_MUTEX_HPP */
