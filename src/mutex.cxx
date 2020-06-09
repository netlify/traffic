#include <traffic/mutex.hpp>

#include <traffic/constants.hpp>

namespace traffic {

void default_delete<TSMutex>::operator () (pointer ptr) const noexcept {
  TSMutexDestroy(ptr);
}

mutex::mutex (native_handle_type handle) noexcept : handle { handle } { }
mutex::mutex () noexcept : handle { TSMutexCreate() } { }

bool mutex::try_lock () noexcept {
  return TSMutexLockTry(this->get()) == traffic::success;
}
void mutex::unlock () noexcept { TSMutexUnlock(this->get()); }
void mutex::lock () noexcept { TSMutexLock(this->get()); }

mutex::native_handle_type mutex::native_handle () const noexcept { return this->get(); }

} /* namespace traffic */
