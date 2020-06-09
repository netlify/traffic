#include <traffic/session.hpp>

namespace traffic {

#if TS_VERSION_MAJOR >= 8
bool session::internal () const noexcept { return TSHttpSsnIsInternal(this->get()); }
int64_t session::id () const noexcept { return TSHttpSsnIdGet(this->get()); }
#endif /* TS_VERSION_MAJOR >= 8 */

} /* namespace traffic */
