#ifndef TRAFFIC_UUID_HPP
#define TRAFFIC_UUID_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSUuid> {
  using pointer = TSUuid;
  void operator () (pointer) const noexcept;
};

struct uuid : private unique_handle<TSUuid> {
  using handle_type::handle_type;
  using handle_type::get;
};

std::string_view to_string (uuid) noexcept;

} /* namespace traffic */

#endif /* TRAFFIC_UUID_HPP */
