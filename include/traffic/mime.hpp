#ifndef TRAFFIC_MIME_HPP
#define TRAFFIC_MIME_HPP

#include <traffic/memory.hpp>
#include <traffic/offset.hpp>
#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSMimeParser> {
  using pointer = TSMimeParser;
  void operator () (pointer ptr) const noexcept;
};

} /* namespace traffic */

namespace traffic::mime {

struct header : private offset {
  using size_type = int;

};

struct parser : private unique_handle<TSMimeParser> {
  parser () noexcept;

  void clear () noexcept;

  using handle_type::operator bool;
  using handle_type::get;
};

} /* namespace traffic::mime */

#endif /* TRAFFIC_MIME_HPP */
