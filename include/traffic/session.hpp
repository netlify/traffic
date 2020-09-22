#ifndef TRAFFIC_SESSION_HPP
#define TRAFFIC_SESSION_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic {

struct session : private view_handle<TSHttpSsn> {
  using resource_type::resource_type;

  #if TS_VERSION_MAJOR >= 8
  [[nodiscard]] bool internal () const noexcept;
  [[nodiscard]] int64_t id () const noexcept;
  #endif /* TS_MAJOR_VERSION >= 8 */

  // TODO: use apex::outcome<int, exception_ptr>
  // int socket () const noexcept;
  // TODO: The below function *could* theoretically be called by our wrapper,
  //       rather than expecting the user to do so. This would allow us to be
  //       exception safe, and reenable as needed
  // TODO: reenable with continue -> TS_EVENT_HTTP_CONTINUE
  //       reenable with error -> TS_EVENT_HTTP_ERROR
  // void reenable () noexcept;
};

} /* namespace traffic */


#endif /* TRAFFIC_SESSION_HPP */
