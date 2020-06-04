#ifndef TRAFFIC_CACHE_HPP
#define TRAFFIC_CACHE_HPP

#include <apex/core/span.hpp>

#include <traffic/memory.hpp>

#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSCacheKey> {
  using pointer = TSCacheKey;
  void operator () (pointer ptr) const noexcept;
};

} /* namespace traffic */

namespace traffic::cache {

enum class error {
  not_ready = TS_CACHE_ERROR_NOT_READY,
  no_doc = TS_CACHE_ERROR_NO_DOC,
  busy = TS_CACHE_ERROR_DOC_BUSY,
};

struct key final : private unique_handle<TSCacheKey> {
  key (apex::span<apex::byte const>) noexcept;

  using handle_type::get;
};

} /* namespace traffic::cache */

#endif /* TRAFFIC_CACHE_HPP */
