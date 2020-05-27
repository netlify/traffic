#ifndef TRAFFIC_ACTION_HPP
#define TRAFFIC_ACTION_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>

#include <cstddef>

namespace traffic {

// TODO: This acts more like a view, but we cant use apex::mixin::handle :/
struct action : private view_handle<TSAction> {
  action (std::nullptr_t) = delete;
  action (pointer) noexcept;

  explicit operator bool () const noexcept;

  [[nodiscard]] bool is_done () const noexcept;
  void cancel () noexcept;
};

} /* namespace traffic */

#endif /* TRAFFIC_ACTION_HPP */
