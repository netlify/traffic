#include <traffic/session.hpp>

namespace traffic {

bool session::is_internal () const noexcept {
  return TSHttpSsnIsInternal(this->get());
}

session::pointer session::get () const noexcept { return this->handle; }


} /* namespace traffic */
