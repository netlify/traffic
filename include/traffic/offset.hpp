#ifndef TRAFFIC_OFFSET_HPP
#define TRAFFIC_OFFSET_HPP

#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic::impl {

struct offset_delete {
  using pointer = TSMLoc;

  offset_delete (TSMBuffer, TSMLoc) noexcept;
  offset_delete (TSMBuffer) noexcept;
  offset_delete () = delete;

  void operator () (pointer) const noexcept;

  TSMBuffer buffer () const noexcept;
  TSMLoc parent () const noexcept;

private:
  TSMBuffer bufp { nullptr };
  TSMLoc base { TS_NULL_MLOC };
};

} /* namespace traffic::impl */

namespace traffic {

// This is a mixin type that uses unique_handle, a custom deleter,
// and adds a few operations so that a user may wrap the TSMLoc type as its
// used around a given interface. AFAICT, the MLoc stands for marhsall location
// however all the APIs use the term 'offset'. Hence the name of this class
struct offset : private unique_handle<TSMLoc, impl::offset_delete> {
  using deleter_type = impl::offset_delete;
  using buffer_type = TSMBuffer;

  using pointer = typename deleter_type::pointer;

  using resource_type::resource_type;
  using resource_type::get;
protected:
  TSMBuffer buffer () const noexcept;
  TSMLoc parent () const noexcept;
};

} /* namespace traffic */

#endif /* TRAFFIC_OFFSET_HPP */
