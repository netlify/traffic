#include <traffic/buffer.hpp>

namespace traffic {

buffer::buffer (TSIOBufferSizeIndex size) noexcept :
  handle { TSIOBufferSizedCreate(size) }
{ }
buffer::buffer () noexcept : handle { TSIOBufferCreate() } { }
buffer::~buffer () noexcept { TSIOBufferDestroy(this->get()); }

buffer::mark_type buffer::mark () const noexcept {
  return TSIOBufferWaterMarkGet(this->get());
}

void buffer::mark (mark_type value) noexcept {
  TSIOBufferWaterMarkSet(this->get(), value);
}

buffer::handle_type buffer::get () const noexcept {
  return this->handle;
}

} /* namespace traffic */
