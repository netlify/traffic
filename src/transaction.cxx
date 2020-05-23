#include <traffic/transaction.hpp>

namespace traffic {

bool transaction::is_websocket () const noexcept {
  return TSHttpTxnIsWebsocket(this->get());
}

bool transaction::is_internal () const noexcept {
  return TSHttpTxnIsInternal(this->get());
}

bool transaction::is_aborted () const noexcept {
  return TSHttpTxnAborted(this->get()) == TS_SUCCESS;
}

transaction::pointer transaction::get () const noexcept { return this->handle; }

} /* namespace traffic */
