#ifndef TRAFFIC_CONTINUATION_HPP
#define TRAFFIC_CONTINUATION_HPP

#include <ts/ts.h>

#include <chrono>

namespace traffic {

enum class thread_pool {
  task = TS_THREAD_POOL_TASK,
  net = TS_THREAD_POOL_NET,
  dns = TS_THREAD_POOL_DNS,
  udp = TS_THREAD_POOL_UDP,
};

// TODO: redesign this type (but keep it available as a lockable type)
struct continuation {
  using callback_type = auto (*)(TSCont, TSEvent, void*) -> void;
  continuation (callback_type const&) noexcept;

  void schedule (std::chrono::milliseconds);

  bool try_lock () noexcept;
  void unlock () noexcept;
  void lock () noexcept;

  TSCont get () const noexcept;

private:
  TSMutex mutex () const noexcept;
  TSCont handle;
};

} /* namespace traffic */

#endif /* TRAFFIC_CONTINUATION_HPP */
