#ifndef TRAFFIC_HOOK_HPP
#define TRAFFIC_HOOK_HPP

#include <traffic/continuation.hpp>
#include <traffic/constants.hpp>

namespace traffic {

// We break up the various hook types into their own categories.
// This results in more functions, but we can then 'enforce' more type
// safety for certain continuation operations.

void global (enum hook::transaction, continuation const&) noexcept;
void global (enum hook::session, continuation const&) noexcept;

// TODO: some of the above hook types are only valid for sessions, others
// for transactions, and others for global hooks. We need to figure out the
// exact combination, and then provide the various function overloads for each
// enum input. This will increase the amount of 'code' to handle, but we'll
// let the type system save us from our mistakes.
} /* namespace traffic */


#endif /* TRAFFIC_HOOK_HPP */
