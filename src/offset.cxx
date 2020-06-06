#include <traffic/offset.hpp>

namespace traffic::impl {

offset_delete::offset_delete (TSMBuffer bufp, pointer base) noexcept :
  bufp { bufp },
  base { base }
{ }

offset_delete::offset_delete (TSMBuffer bufp) noexcept :
  offset_delete { bufp, TS_NULL_MLOC }
{ }

// TODO: log the return code when it's *not* a TS_SUCCESS
void offset_delete::operator ()(pointer ptr) const noexcept {
  apex::ignore = TSHandleMLocRelease(this->buffer(), this->parent(), ptr);
}

TSMBuffer offset_delete::buffer () const noexcept { return this->bufp; }
TSMLoc offset_delete::parent () const noexcept { return this->base; }

} /* namespace traffic::impl */

namespace traffic {

TSMBuffer offset::buffer () const noexcept { return this->storage.get_deleter().buffer(); }
TSMLoc offset::parent () const noexcept { return this->storage.get_deleter().parent(); }

} /* namespace traffic */
