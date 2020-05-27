#ifndef TRAFFIC_SESSION_HPP
#define TRAFFIC_SESSION_HPP

#include <ts/ts.h>

namespace traffic {

struct session {
  using pointer = TSHttpSsn;

  session (pointer) noexcept;

  pointer get () const noexcept;

  int64_t id () const noexcept;

  [[nodiscard]] bool is_internal () const noexcept;

  // TODO: use apex::outcome<int, exception_ptr>
  // int socket () const noexcept;
  // TODO: The below function *could* theoretically be called by our wrapper,
  //       rather than expecting the user to do so. This would allow us to be
  //       exception safe, and reenable as needed
  // TODO: reenable with continue -> TS_EVENT_HTTP_CONTINUE
  //       reenable with error -> TS_EVENT_HTTP_ERROR
  // void reenable () noexcept;

private:
  pointer handle;
};

} /* namespace traffic */


#endif /* TRAFFIC_SESSION_HPP */
