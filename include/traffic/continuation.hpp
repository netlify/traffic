#ifndef TRAFFIC_CONTINUATION_HPP
#define TRAFFIC_CONTINUATION_HPP

#include <traffic/memory.hpp>
#include <traffic/cache.hpp>
#include <ts/ts.h>

#include <chrono>

namespace traffic {

// The design of traffic::continuation is such that it meets a few known
// standard C++ 'named requirements' (aka, legacy concepts). These include
// Lockable
// Callable
//
// We have a few goals for the design of traffic::continuation<T>
// 1) Users are passed a reference to `this` continuation as the first
//    parameter rather than the TSCont type, which they can retrieve via
//    .get() (though lifetimes have to be understood by the user, so it isn't
//    bulletproof)
// 2) Continuation takes a type `T` as a template parameter. This type is
//    stored as a value inside the continuation, and is returned via `.value()`
//    by lvalue reference. We use static_asserts to ensure some guarantees
//    about the object's ability to be constructed or destructed
// 3) We specialize continuation<void> as the base class so we can put *some*
//    code inside a .cxx file. This will reduce compile time overhead when it
//    isn't really needed
// 4) the TSCont type is constructed with a mutex by default, i.e.,
//    TSMutexCreate(). We will need a way to 'share' these mutexes (mutices?)
//    across multiple continuations that may share data. This has yet to be
//    designed, however we will most likely NOT use the traffic::mutex type
// 5) TSCont meets the Lockable named requirement, and will thus be usable
//    as such.
// 6) If the first parameter of the continuation is continuation&, `*this` is
//    passed in as the first parameter.
//    If the first parameter of the continuation is traffic::event, we pass
//    it and the value the continuation manages.
//    If the first parameter of the continuation is value_type [const]&, we
//    simply pass the value into the function
//
//
// A few alternative solutions:
// use std::any so continuation can stay type erased to a degree (after all,
// we're simply storing a function object, which can be stored inside of
// std::function. We can then use std::any to the actual parameter needed,
// however in practice we'll just have users store any data inside the lambda
// they pass in, and we just pass continuation& as needed.

template <>
struct default_delete<TSCont> {
  using pointer = TSCont;
  void operator () (pointer ptr) const noexcept;
};

// TODO: redesign this type (but keep it available as a lockable type)
struct [[clang::capability("mutex")]] continuation : protected unique_handle<TSCont> {
  using native_handle_type = TSMutex;

  [[clang::try_acquire_capability(true)]] bool try_lock () noexcept;
  [[clang::acquire_capability]] void unlock () noexcept;
  [[clang::release_capability]] void lock () noexcept;

  native_handle_type native_handle () const noexcept;

};

} /* namespace traffic */

#endif /* TRAFFIC_CONTINUATION_HPP */
