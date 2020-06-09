#include <traffic/transaction.hpp>
#include <traffic/constants.hpp>

namespace {

using create_headers = auto (*)(TSHttpTxn, TSMBuffer*, TSMLoc*) -> TSReturnCode;

auto request_or_response (create_headers fn, TSHttpTxn txn) {
  TSMBuffer bufp { };
  TSMLoc offset { };
  auto result = fn(txn, std::addressof(bufp), std::addressof(offset));
  if (result != traffic::success) { /* TODO: Log this error/handle 'failure' state */ }
  return traffic::http::header(offset, bufp);
}

} /* nameless namespace */

namespace traffic {

http::header transaction::cached_response () const noexcept {
  return ::request_or_response(TSHttpTxnCachedRespGet, this->get());
}

http::header transaction::cached_request () const noexcept {
  return ::request_or_response(TSHttpTxnCachedReqGet, this->get());
}

http::header transaction::server_response () const noexcept {
  return ::request_or_response(TSHttpTxnServerRespGet, this->get());
}

http::header transaction::server_request () const noexcept {
  return ::request_or_response(TSHttpTxnServerReqGet, this->get());
}

http::header transaction::response () const noexcept {
  return ::request_or_response(TSHttpTxnClientRespGet, this->get());
}

http::header transaction::request () const noexcept {
  return ::request_or_response(TSHttpTxnClientReqGet, this->get());
}

struct session transaction::session () const noexcept {
  return traffic::session { TSHttpTxnSsnGet(this->get()) };
}

std::string_view transaction::tag () const noexcept {
  return TSHttpTxnPluginTagGet(this->get());
}

bool transaction::websocket () const noexcept {
  return TSHttpTxnIsWebsocket(this->get());
}

bool transaction::internal () const noexcept {
  return TSHttpTxnIsInternal(this->get());
}

bool transaction::aborted () const noexcept {
  return TSHttpTxnAborted(this->get()) == traffic::success;
}

//url transaction::cache_lookup_url () const noexcept {
//  return TSHttpTxnCacheLookupUrlGet(
//    this->get(),
//}

} /* namespace traffic */
