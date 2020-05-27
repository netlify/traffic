#ifndef TRAFFIC_BUFFER_HPP
#define TRAFFIC_BUFFER_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>
#include <cstdint>

namespace traffic {

template <> struct default_delete<TSIOBuffer> {
  using pointer = TSIOBuffer;
  void operator () (pointer ptr) const noexcept;
};

// NOT a marshal buffer, perhaps make the distinction?
struct buffer : private unique_handle<TSIOBuffer> {
  using mark_type = std::int64_t;

  buffer (TSIOBufferSizeIndex) noexcept;
  buffer () noexcept;
  ~buffer() noexcept = default;

  mark_type mark () const noexcept;
  void mark (mark_type) noexcept;
};

} /* namespace traffic */

#endif /* TRAFFIC_BUFFER_HPP */
