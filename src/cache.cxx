#include <traffic/cache.hpp>

namespace traffic {

void default_delete<TSCacheKey>::operator () (pointer ptr) const noexcept {
  TSCacheKeyDestroy(ptr);
}

} /* namespace traffic */

namespace traffic::cache {

key::key (apex::span<apex::byte const> digest) noexcept :
  unique_handle<TSCacheKey> { TSCacheKeyCreate() }
{
  TSCacheKeyDigestSet(
    this->get(),
    reinterpret_cast<char const*>(digest.data()),
    digest.size());
}

} /* namespace traffic::cache */
