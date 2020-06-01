#include <traffic/io.hpp>

namespace traffic {

void default_delete<TSIOBufferReader>::operator () (pointer ptr) const noexcept {
  TSIOBufferReaderFree(ptr);
}

void default_delete<TSIOBuffer>::operator () (pointer ptr) const noexcept {
  TSIOBufferDestroy(ptr);
}

} /* namespace traffic */

namespace traffic::io {

bool stream::try_lock () noexcept {
  return TSMutexLockTry(this->native_handle()) == TS_SUCCESS;
}

void stream::unlock () noexcept { return TSMutexUnlock(this->native_handle()); }
void stream::lock () noexcept { return TSMutexLock(this->native_handle()); }

stream::native_handle_type stream::native_handle () const noexcept {
  return TSVIOMutexGet(this->get());
}

buffer::buffer (TSIOBufferSizeIndex size) noexcept :
  unique_handle<TSIOBuffer> { TSIOBufferSizedCreate(size) }
{ }

buffer::buffer (stream const& s) noexcept :
  unique_handle<TSIOBuffer> { TSVIOBufferGet(s.get()) }
{ }

buffer::buffer () noexcept :
  unique_handle<TSIOBuffer> { TSIOBufferCreate() }
{ }

buffer::mark_type buffer::mark () const noexcept {
  return TSIOBufferWaterMarkGet(this->get());
}

void buffer::mark (mark_type value) noexcept {
  TSIOBufferWaterMarkSet(this->get(), value);
}

reader::reader (reader const& that) noexcept :
  unique_handle<TSIOBufferReader> { TSIOBufferReaderClone(that.get()) }
{ }

reader::reader (stream const& s) noexcept :
  unique_handle<TSIOBufferReader> { TSVIOReaderGet(s.get()) }
{ }

reader::reader (buffer const& b) noexcept :
  unique_handle<TSIOBufferReader> { TSIOBufferReaderAlloc(b.get()) }
{ }

} /* namespace traffic::io */
