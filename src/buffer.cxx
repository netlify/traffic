#include <traffic/buffer.hpp>

namespace traffic {

// TODO: log the return code when it is *not* a TS_SUCCESS
// additionally, consider simply panicking so we don't end up in an incorrect
// state.
void default_delete<TSMBuffer>::operator () (pointer ptr) const noexcept {
  apex::ignore = TSMBufferDestroy(ptr);
}

} /* namespace traffic */
