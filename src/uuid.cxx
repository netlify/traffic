#include <traffic/uuid.hpp>

namespace traffic {

void default_delete<TSUuid>::operator () (pointer ptr) const noexcept {
  TSUuidDestroy(ptr);
}

std::string_view to_string (uuid value) noexcept {
  return TSUuidStringGet(value.get());
}

} /* namespace traffic */
