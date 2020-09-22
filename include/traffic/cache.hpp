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

struct key final : private unique_handle<TSCacheKey> {
  key (apex::span<apex::byte const>) noexcept;

  using resource_type::get;
};

} /* namespace traffic::cache */

#endif /* TRAFFIC_CACHE_HPP */
