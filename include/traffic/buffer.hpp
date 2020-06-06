#ifndef TRAFFIC_BUFFER_HPP
#define TRAFFIC_BUFFER_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSMBuffer> {
  using pointer = TSMBuffer;
  void operator () (pointer) const noexcept;
};

struct buffer : private unique_handle<TSMBuffer> {
  using handle_type::operator bool;
  using handle_type::get;
};

} /* namespace traffic */

#endif /* TRAFFIC_BUFFER_HPP */
