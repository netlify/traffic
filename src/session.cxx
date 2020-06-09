#include <traffic/session.hpp>

namespace traffic {

bool session::internal () const noexcept { return TSHttpSsnIsInternal(this->get()); }
int64_t session::id () const noexcept { return TSHttpSsnIdGet(this->get()); }


} /* namespace traffic */
