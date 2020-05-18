#include <traffic/memory.hpp>
#include <ts/ts.h>

#include <string>

#include <cstring>

// This is information taken directly from the mgmtapi.h header.  We're just
// recreating what the macro does. This might break in the future, but it's
// better than using a macro without better tracking.
// While this will allocate *some* memory, we keep it thread local, clear our
// changes, and (minus the file name), the call to `std::to_string` shouldn't
// allocate due to small string optimizations.
// This will be easier to keep track of once we kick out ATS logging in other
// plugins.
// TODO: This just needs to be cleaned up. It's... gross 😑
void* operator new (std::size_t size, traffic::track_t, char const* file, std::size_t length, int line) noexcept {
  static thread_local std::string path { "memory/" };
  path.reserve(length);
  path.append(file)
      .append(":")
      .append(std::to_string(line)); // this to_string will ALWAYS be a small object
  auto ptr = _TSmalloc(size, path.c_str());
  // This is effectively just setting the 'length' to index
  path.erase(__builtin_strlen("memory/")); // erase everything after "memory/", but don't deallocate
  return ptr;
}
