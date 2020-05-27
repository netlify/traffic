#include <traffic/buffer.hpp>

namespace traffic {

void default_delete<TSIOBuffer>::operator () (pointer ptr) const noexcept {
  TSIOBufferDestroy(ptr);
}

buffer::buffer (TSIOBufferSizeIndex size) noexcept :
  handle { TSIOBufferSizedCreate(size) }
{ }
buffer::buffer () noexcept :
  handle { TSIOBufferCreate() }
{ }

buffer::mark_type buffer::mark () const noexcept {
  return TSIOBufferWaterMarkGet(this->get());
}

void buffer::mark (mark_type value) noexcept {
  TSIOBufferWaterMarkSet(this->get(), value);
}

} /* namespace traffic */
