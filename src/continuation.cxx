#include <traffic/continuation.hpp>

namespace traffic {

void default_delete<TSCont>::operator () (pointer ptr) const noexcept {
  TSContDestroy(ptr);
}

bool continuation::try_lock () noexcept {
  return TSMutexLockTry(this->native_handle()) == TS_SUCCESS;
}

void continuation::unlock () noexcept { return TSMutexUnlock(this->native_handle()); }
void continuation::lock () noexcept { return TSMutexLock(this->native_handle()); }

TSMutex continuation::native_handle () const noexcept {
  return TSContMutexGet(this->get());
}

} /* namespace traffic */
