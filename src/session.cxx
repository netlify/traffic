#include <traffic/session.hpp>

namespace traffic {

bool session::internal () const noexcept {
  return TSHttpSSnIsInternal(this->get());
}

session::pointer session::get () const noexcept { return this->handle; }


} /* namespace traffic */
