#ifndef TRAFFIC_SESSION_HPP
#define TRAFFIC_SESSION_HPP

#include <ts/ts.h>

struct session {
  using pointer = TSHttpSsn;

  session (pointer) noexcept;

  pointer get () const noexcept;

  int64_t id () const noexcept;

  [[nodiscard]] bool is_internal () const noexcept;

  // TODO: use apex::outcome<int, exception_ptr>
  // int socket () const noexcept;
  // TODO: The below function *could* theoretically be called by our wrapper,
  //       rather than expecting the user to do so.
  // TODO: reenable with continue -> TS_EVENT_HTTP_CONTINUE
  //       reenable with error -> TS_EVENT_HTTP_ERROR
  // void reenable () noexcept;

private:
  pointer handle;
};

#endif /* TRAFFIC_SESSION_HPP */
