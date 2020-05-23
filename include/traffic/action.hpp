#ifndef TRAFFIC_ACTION_HPP
#define TRAFFIC_ACTION_HPP

#include <ts/ts.h>

#include <cstddef>

namespace traffic {

struct action {
  using pointer = TSAction;

  action (std::nullptr_t) = delete;
  action (pointer) noexcept;

  explicit operator bool () const noexcept;

  pointer get () const noexcept;

  void cancel () noexcept;

private:
  pointer handle;
};

} /* namespace traffic */

#endif /* TRAFFIC_ACTION_HPP */
