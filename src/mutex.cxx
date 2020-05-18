#include <traffic/mutex.hpp>

namespace traffic {

mutex::mutex (native_handle_type handle) noexcept : handle { handle } { }
mutex::mutex () noexcept : handle { TSMutexCreate() } { }
mutex::~mutex () noexcept { if (*this) { TSMutexDestroy(this->get()); } }

mutex::operator bool () const noexcept { return this->get(); }

bool mutex::try_lock () noexcept {
  return TSMutexLockTry(this->get()) == TS_SUCCESS;
}
void mutex::unlock () noexcept { TSMutexUnlock(this->get()); }
void mutex::lock () noexcept { TSMutexLock(this->get()); }

mutex::native_handle_type mutex::native_handle () const noexcept { return this->get(); }
mutex::native_handle_type mutex::get () const noexcept { return this->handle; }

} /* namespace traffic */
