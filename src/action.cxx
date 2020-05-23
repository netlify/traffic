#include <traffic/action.hpp>

namespace traffic {

action::action (pointer handle) noexcept : handle { handle } { }

action::operator bool () const noexcept { return TSActionDone(this->get()); }

action::pointer action::get () const noexcept { return this->handle; }

void action::cancel () noexcept {
  if (not this->get()) { return; }
  TSActionCancel(this->get());
}

} /* namespace traffic */
