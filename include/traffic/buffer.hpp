#ifndef TRAFFIC_BUFFER_HPP
#define TRAFFIC_BUFFER_HPP

#include <ts/ts.h>
#include <cstdint>

namespace traffic {

// NOT a marshal buffer, perhaps make the distinction?
struct buffer {
  using handle_type = TSIOBuffer;
  using mark_type = std::int64_t;

  buffer (TSIOBufferSizeIndex) noexcept;
  buffer () noexcept;
  ~buffer() noexcept;

  mark_type mark () const noexcept;
  void mark (mark_type) noexcept;

  handle_type get () const noexcept;

private:
  handle_type handle;
};

} /* namespace traffic */

#endif /* TRAFFIC_BUFFER_HPP */
