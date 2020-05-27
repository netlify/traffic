#ifndef TRAFFIC_LOCATION_HPP
#define TRAFFIC_LOCATION_HPP

#include <traffic/memory.hpp>

namespace traffic {

struct default_delete<TSMLoc> {
  using pointer = TSMLoc;
  void operator () (pointer) const noexcept;
};

struct location : private unique_handle<TSMLoc> { };

} /* namespace traffic */

#endif /* TRAFFIC_LOCATION_HPP */
