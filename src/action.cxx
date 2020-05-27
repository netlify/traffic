#include <traffic/action.hpp>

namespace traffic {

action::action (pointer handle) noexcept :
  view_handle<TSAction> { handle }
{ }

action::operator bool () const noexcept { return TSActionDone(this->get()); }

void action::cancel () noexcept {
  if (not this->get()) { return; }
  TSActionCancel(this->get());
}

} /* namespace traffic */
