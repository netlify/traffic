#include <traffic/continuation.hpp>

namespace traffic {



bool continuation::try_lock () noexcept {
  return TSMutexLockTry(this->mutex()) == TS_SUCCESS;
}

void continuation::unlock () noexcept { return TSMutexUnlock(this->mutex()); }
void continuation::lock () noexcept { return TSMutexLock(this->mutex()); }

TSMutex continuation::mutex () const noexcept {
  return TSContMutexGet(this->get());
}

} /* namespace traffic */
