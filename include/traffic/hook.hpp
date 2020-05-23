#ifndef TRAFFIC_HOOK_HPP
#define TRAFFIC_HOOK_HPP

#include <traffic/continuation.hpp>

// We break up the various hook types into their own categories.
// This results in more functions, but we can then 'enforce' more type
// safety for certain continuation operations.

namespace traffic::hook {

enum class lookup { complete = TS_HTTP_CACHE_LOOKUP_COMPLETE_HOOK, };
enum class select { alternate = TS_HTTP_SELECT_ALT_HOOK, };
enum class cache { read = TS_HTTP_READ_CACHE_HDR_HOOK, };
enum class os { dns = TS_HTTP_OS_DNS_HOOK, };

enum class transaction {
  start = TS_HTTP_TXN_START_HOOK,
  close = TS_HTTP_TXN_CLOSE_HOOK,
};

enum class session {
  start = TS_HTTP_SSN_START_HOOK,
  close = TS_HTTP_SSN_CLOSE_HOOK,
};

enum class transform {
  response = TS_HTTP_RESPONSE_TRANSFORM_HOOK,
  request = TS_HTTP_REQUEST_TRANSFORM_HOOK,
};

enum class remap {
  before = TS_HTTP_PRE_REMAP_HOOK,
  after = TS_HTTP_POST_REMAP_HOOK,
};

enum class response {
  read = TS_HTTP_READ_RESPONSE_HDR_HOOK,
  send = TS_HTTP_SEND_RESPONSE_HDR_HOOK,
};

enum class request {
  read = TS_HTTP_READ_REQUEST_HDR_HOOK,
  send = TS_HTTP_SEND_REQUEST_HDR_HOOK,
};

enum class connection {
  start = TS_VCONN_START_HOOK,
  close = TS_VCONN_CLOSE_HOOK,
};

#if TS_MAJOR_VERSION >= 9
enum class outbound {
  start = TS_VCONN_OUTBOUND_START_HOOK,
  close = TS_VCONN_OUTBOUND_CLOSE_HOOK,
};
#endif /* TS_MAJOR_VERSION >= 9 */

enum class ssl {
  #if TS_MAJOR_VERSION >= 9
  hello = TS_SSL_CLIENT_HELLO_HOOK,
  server = TS_SSL_VERIFY_SERVER_HOOK,
  #endif /* TS_MAJOR_VERSION >= 9 */
  first = TS_SSL_FIRST_HOOK,
  cert = TS_SSL_CERT_HOOK,
  servername = TS_SSL_SERVERNAME_HOOK,
  client = TS_SSL_VERIFY_CLIENT_HOOK,
  last = TS_SSL_LAST_HOOK,
};

void global (enum transaction, continuation const&) noexcept;
void global (enum session, continuation const&) noexcept;

// TODO: some of the above hook types are only valid for sessions, others
// for transactions, and others for global hooks. We need to figure out the
// exact combination, and then provide the various function overloads for each
// enum input. This will increase the amount of 'code' to handle, but we'll
// let the type system save us from our mistakes.

} /* namespace traffic::hook */

#endif /* TRAFFIC_HOOK_HPP */
