#ifndef TRAFFIC_MEMORY_HPP
#define TRAFFIC_MEMORY_HPP

#include <cstddef>

namespace traffic {

struct track_t { };
inline constexpr track_t track { };

} /* namespace traffic */

// TODO: Replace with {apex|std}::source_location when possible. That said,
// this works with Clang 10 and GCC.
// This replaces using TSmalloc directly
void* operator new (
  std::size_t,
  traffic::track_t,
  char const* file = __builtin_FILE(),
  std::size_t length = __builtin_strlen(__builtin_strlen("memory/") + __builtin_FILE()) + 1 + __builtin_strlen(__builtin_FILE()),
  int line = __builtin_LINE()) noexcept;

// Required to be defined, but only called if new throws, which ours does not
void operator delete (void*, traffic::track_t, char const*, int);

#endif /* TRAFFIC_MEMORY_HPP */
