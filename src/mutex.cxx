#include <traffic/mutex.hpp>

namespace traffic {

void default_delete<TSMutex>::operator () (pointer ptr) const noexcept {
  TSMutexDestroy(ptr);
}

mutex::mutex (native_handle_type handle) noexcept : handle { handle } { }
mutex::mutex () noexcept : handle { TSMutexCreate() } { }

bool mutex::try_lock () noexcept {
  return TSMutexLockTry(this->get()) == TS_SUCCESS;
}
void mutex::unlock () noexcept { TSMutexUnlock(this->get()); }
void mutex::lock () noexcept { TSMutexLock(this->get()); }

mutex::native_handle_type mutex::native_handle () const noexcept { return this->get(); }

} /* namespace traffic */
