#ifndef TRAFFIC_IO_HPP
#define TRAFFIC_IO_HPP

#include <apex/core/span.hpp>
#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSIOBufferReader> {
  using pointer = TSIOBufferReader;
  void operator () (pointer ptr) const noexcept;
};

template <> struct default_delete<TSIOBuffer> {
  using pointer = TSIOBuffer;
  void operator () (pointer ptr) const noexcept;
};

} /* namespace traffic */

namespace traffic::io {

struct stream final : private view_handle<TSVIO> {
  using native_handle_type = TSMutex;

  bool try_lock () noexcept;
  void unlock () noexcept;
  void lock () noexcept;

  native_handle_type native_handle () const noexcept;

  using resource_type::get;
};

struct buffer : private unique_handle<TSIOBuffer> {
  using mark_type = std::int64_t;

  buffer (buffer const&) = delete;

  buffer (TSIOBufferSizeIndex) noexcept;
  buffer (stream const&) noexcept;
  buffer () noexcept;
  ~buffer () noexcept = default;

  mark_type mark () const noexcept;
  void mark (mark_type) noexcept;

  using resource_type::get;
private:
  buffer (pointer) noexcept;
};

// NOTE: the underlying TSIOBufferReader interface changed between 8 and 9
//struct reader : private unique_handle<TSIOBufferReader> {
//  reader (reader const&) noexcept;
//
//  reader (stream const&) noexcept;
//  reader (buffer const&) noexcept;
//private:
//  reader (pointer) noexcept;
//};

} /* namespace traffic::io */

#endif /* TRAFFIC_IO_HPP */
