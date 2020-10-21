#include <traffic/mutex.hpp>

#include <traffic/constants.hpp>

namespace traffic {

void default_delete<TSMutex>::operator () (pointer ptr) const noexcept {
  TSMutexDestroy(ptr);
}

mutex::mutex () noexcept : resource_type { TSMutexCreate() } { }

bool mutex::try_lock () noexcept {
  return TSMutexLockTry(this->get()) == traffic::success;
}
void mutex::unlock () noexcept { TSMutexUnlock(this->get()); }
void mutex::lock () noexcept { TSMutexLock(this->get()); }

mutex::native_handle_type mutex::native_handle () const noexcept { return this->get(); }

borrowed_mutex::borrowed_mutex (TSCont cont) noexcept :
  borrowed_mutex(TSContMutexGet(cont))
{ }

bool borrowed_mutex::try_lock () noexcept {
  return TSMutexLockTry(this->get()) == traffic::success;
}

void borrowed_mutex::unlock () noexcept { TSMutexUnlock(this->get()); }
void borrowed_mutex::lock () noexcept { TSMutexLock(this->get()); }

borrowed_mutex::native_handle_type borrowed_mutex::native_handle () const noexcept {
  return this->get();
}

} /* namespace traffic */
