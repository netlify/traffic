#ifndef TRAFFIC_CONSTANTS_HPP
#define TRAFFIC_CONSTANTS_HPP

#include <ts/apidefs.h>
#include <type_traits>

// All enum classes are declared here so that they can be more easily
// shared amongst the API. Additionally, it helps reduce 'header clutter',
// as constants rarely change, but take up a large amount of lines and make it
// difficult to see/read the APIs they are used with.
// They are (mostly) ordered by namespace.
//
// No functions are forward declared here
// This header is meant to have minimal impact
//
// TODO: Add TSOverridableConfigKey values
namespace traffic {

// not a class, but that's to more closely mimic the TS C API
// i.e., we can do traffic::success and traffic::error
enum result : std::underlying_type_t<TSReturnCode> {
  success = TS_SUCCESS,
  error = TS_ERROR,
};

enum class pool : std::underlying_type_t<TSThreadPool> {
  task = TS_THREAD_POOL_TASK,
  net = TS_THREAD_POOL_NET,
  dns = TS_THREAD_POOL_DNS,
  udp = TS_THREAD_POOL_UDP,
};

enum class lookup : std::underlying_type_t<TSLookingUpType> {
  undefined = TS_LOOKUP_UNDEFINED_LOOKUP,
  router = TS_LOOKUP_INCOMING_ROUTER,
  origin = TS_LOOKUP_ORIGIN_SERVER,
  proxy = TS_LOOKUP_PARENT_PROXY,
  host = TS_LOOKUP_HOST_NONE,
};

enum class parse : std::underlying_type_t<TSParseResult> {
  error = TS_PARSE_ERROR,
  done = TS_PARSE_DONE,
  next = TS_PARSE_CONT,
};

} /* namespace traffic */

namespace traffic::http {

enum class type : std::underlying_type_t<TSHttpType> {
  response = TS_HTTP_TYPE_RESPONSE,
  unknown = TS_HTTP_TYPE_UNKNOWN,
  request = TS_HTTP_TYPE_REQUEST,
};

// No underlying type because we secretly convert it to and from a string_view
// for use with the TSHttpHdrMethod(Get|Set) API
// Unlike everything else, this is the ONE TIME we will use SCREAMING_SNAKE_CASE
// and that is because of other programming language APIs using the upper case
// names. Also delete is a keyword :'(
enum class method {
  UNKNOWN,
  GET,
  HEAD,
  CONNECT,
  DELETE,
  OPTIONS,
  PURGE,
  PUT,
  TRACE,
  PUSH,
};

// These constants are used for HTTP status codes. However we don't currently
// have an apex::status_code type (like the one that was proposed by Niall
// Douglass. At some point we might, and then specialization and interface
// hooks will allow a more expressive API. Until then, however, we just define
// them as their values.
// TODO: Use the TSHttpStatus names where possible
enum class status : std::underlying_type_t<TSHttpStatus> {
  // informational
  continued = 100, // this is actually 100 CONTINUE
  switching_protocols = 101,
  processing = 102,

  // success
  ok = 200,
  created = 201,
  accepted = 202,
  non_authoritative_information = 203,
  no_content = 204,
  reset_content = 205,
  partial_content = 206,
  multi_status = 207,
  already_reported = 208,
  instance_manipulation_used = 226,

  // redirection
  multiple_choices = 300,
  moved_permanently = 301,
  found = 302,
  see_other = 303,
  not_modified = 304,
  use_proxy = 305,
  temporary_redirect = 307,
  permanent_redirect = 308,

  // client error
  bad_request = 400,
  unauthorized = 401,
  payment_required = 402,
  forbidden = 403,
  not_found = 404,
  method_not_allowed = 405,
  not_acceptable = 406,
  proxy_authentication_required = 407,
  request_timeout = 408,
  conflict = 409,
  gone = 410,
  length_required = 411,
  precondition_failed = 412,
  payload_too_large = 413,
  request_uri_too_long = 414,
  unsupported_media_type = 415,
  requested_range_not_satisfiable = 416,
  expectation_failed = 417,
  im_a_teapot = 418,
  misdirected_request = 421,
  unprocessable_entity = 422,
  locked = 423,
  failed_dependency = 424,
  upgrade_required = 426,
  precondition_required = 428,
  too_many_requests = 429,
  request_header_fields_too_large = 431,
  connection_closed_without_response = 444,
  unavailable_for_legal_reasons = 451,
  client_closed_request = 499,

  // server error
  internal = 500,
  not_implemented = 501,
  bad_gateway = 502,
  service_unavailable = 503,
  gateway_timeout = 504,
  version_not_supported = 505,
  variant_also_negotiates = 506,
  insufficient_storage = 507,
  loop_detected = 508,
  not_extended = 510,
  network_authentication_required = 511,
  network_connect_timeout_error = 599,
};

} /* namespace traffic::http */

// TODO: consider moving all TS_HTTP_*_HOOKs to traffic::http::hook?
// TODO: apply the underlying_type_t for the TSHttpHookId values and others
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

#if TS_MAJOR_VERSION >= 8
enum class connection {
  start = TS_VCONN_START_HOOK,
  close = TS_VCONN_CLOSE_HOOK,
};
#endif /* TS_MAJOR_VERSION >= 8 */

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
  #if TS_MAJOR_VERSION >= 8
  client = TS_SSL_VERIFY_CLIENT_HOOK,
  #endif /* TS_MAJOR_VERSION >= 8 */
  last = TS_SSL_LAST_HOOK,
};

enum class lifecycle : std::underlying_type_t<TSLifecycleHookID> {
  ports_initialized = TS_LIFECYCLE_PORTS_INITIALIZED_HOOK,
  ports_ready = TS_LIFECYCLE_PORTS_READY_HOOK,
  cache_ready = TS_LIFECYCLE_CACHE_READY_HOOK,
  message = TS_LIFECYCLE_MSG_HOOK,
  client = TS_LIFECYCLE_CLIENT_SSL_CTX_INITIALIZED_HOOK,
  server = TS_LIFECYCLE_SERVER_SSL_CTX_INITIALIZED_HOOK,
};

} /* namespace traffic::hook */

namespace traffic::cache {

enum class error : std::underlying_type_t<TSCacheError> {
  not_ready = TS_CACHE_ERROR_NOT_READY,
  missing = TS_CACHE_ERROR_NO_DOC,
  busy = TS_CACHE_ERROR_DOC_BUSY,
};

enum class lookup : std::underlying_type_t<TSCacheLookupResult> {
  skipped = TS_CACHE_LOOKUP_SKIPPED,
  stale = TS_CACHE_LOOKUP_HIT_STALE,
  fresh = TS_CACHE_LOOKUP_HIT_FRESH,
  miss = TS_CACHE_LOOKUP_MISS,
};

enum class scan : std::underlying_type_t<TSCacheScanResult> {
  done = TS_CACHE_SCAN_RESULT_DONE,
  next = TS_CACHE_SCAN_RESULT_CONTINUE,
  remove = TS_CACHE_SCAN_RESULT_DELETE,
  purge = TS_CACHE_SCAN_RESULT_DELETE_ALL_ALTERNATES,
  update = TS_CACHE_SCAN_RESULT_UPDATE,
  retry = TS_CACHE_SCAN_RESULT_RETRY,
};

} /* namespace traffic::cache */

// TODO: Turn some "failures" into error enums
// with make_error_code, category, etc.
// Because we will be taking the 'event queue' route, it's possible for
// us to put all 'failed' events into a single event error category,
// and use that in combination with our eventual C++ coroutines work.
// Additionally, this means we could *technically* hide these failure values
// from the public API. Users would only ever receive an apex::outcome<T, std::error_code>
// with the information needed to be logged/reported.
//
// NOTE: The above is a musing and may or may not be implemented
namespace traffic::event {

enum class status {
  immediate = TS_EVENT_IMMEDIATE,
  timeout = TS_EVENT_TIMEOUT,
  error = TS_EVENT_ERROR,
  none = TS_EVENT_NONE,
};

enum class error {
  connect  = TS_EVENT_NET_CONNECT_FAILED,
  accept = TS_EVENT_NET_ACCEPT_FAILED,
};

enum class cache {
  cache_open_read_failed = TS_EVENT_CACHE_OPEN_READ_FAILED,
  cache_open_write = TS_EVENT_CACHE_OPEN_WRITE,
  cache_open_write_failed = TS_EVENT_CACHE_OPEN_WRITE_FAILED,
  cache_remove = TS_EVENT_CACHE_REMOVE,
  cache_remove_failed = TS_EVENT_CACHE_REMOVE_FAILED,
  // TODO: look into whether this can be split into its own category
  cache_scan = TS_EVENT_CACHE_SCAN,
  cache_scan_failed = TS_EVENT_CACHE_SCAN_FAILED,
  cache_scan_object = TS_EVENT_CACHE_SCAN_OBJECT,
  cache_scan_operation_blocked = TS_EVENT_CACHE_SCAN_OPERATION_BLOCKED,
  cache_scan_operation_failed = TS_EVENT_CACHE_SCAN_OPERATION_FAILED,
  cache_scan_done = TS_EVENT_CACHE_SCAN_DONE,
  cache_lookup = TS_EVENT_CACHE_LOOKUP,
  cache_read = TS_EVENT_CACHE_READ,
  cache_delete = TS_EVENT_CACHE_DELETE,
  cache_write = TS_EVENT_CACHE_WRITE,
  cache_write_header = TS_EVENT_CACHE_WRITE_HEADER,
  cache_close = TS_EVENT_CACHE_CLOSE,
  cache_lookup_ready = TS_EVENT_CACHE_LOOKUP_READY,
  cache_lookup_complete = TS_EVENT_CACHE_LOOKUP_COMPLETE,
  cache_read_ready = TS_EVENT_CACHE_READ_READY,
  cache_read_complete = TS_EVENT_CACHE_READ_COMPLETE,
};

enum class inbound {
  inactivity_timeout = TS_EVENT_VCONN_INACTIVITY_TIMEOUT,
  active_timeout = TS_EVENT_VCONN_ACTIVE_TIMEOUT,
  write_complete = TS_EVENT_VCONN_WRITE_COMPLETE,
  read_complete = TS_EVENT_VCONN_READ_COMPLETE,
  write_ready = TS_EVENT_VCONN_WRITE_READY,
  read_ready = TS_EVENT_VCONN_READ_READY,
#if TS_VERSION_MAJOR >= 8
  start = TS_EVENT_VCONN_START,
  close = TS_EVENT_VCONN_CLOSE,
#endif /* TS_VERSION_MAJOR >= 8 */
  eos = TS_EVENT_VCONN_EOS,
};

enum class net {
  connect_failed = TS_EVENT_NET_CONNECT_FAILED,
  accept_failed = TS_EVENT_NET_ACCEPT_FAILED,
  connect = TS_EVENT_NET_CONNECT,
  accept = TS_EVENT_NET_ACCEPT,
};

} /* namespace traffic::event */

// All overrides go here
namespace traffic {

constexpr bool operator == (TSReturnCode c, result r) noexcept {
  return static_cast<std::underlying_type_t<TSReturnCode>>(c) == r;
}

constexpr bool operator != (TSReturnCode c, result r) noexcept {
  return not (c == r);
}

constexpr bool operator == (result r, TSReturnCode c) noexcept {
  return c == r;
}

constexpr bool operator != (result r, TSReturnCode c) noexcept {
  return c != r;
}

} /* namespace traffic */

#endif /* TRAFFIC_CONSTANTS_HPP */
