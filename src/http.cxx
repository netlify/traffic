#include <traffic/http.hpp>

#include <apex/core/utility.hpp>
#include <apex/core/array.hpp>

namespace {

using namespace traffic::http;

static constexpr std::array informational_status_codes {
  status::continued,
  status::switching_protocols,
  status::processing
};

static constexpr std::array success_status_codes {
  status::ok,
  status::created,
  status::accepted,
  status::non_authoritative_information,
  status::no_content,
  status::reset_content,
  status::partial_content,
  status::multi_status,
  status::already_reported,
  status::instance_manipulation_used
};

static constexpr std::array redirection_status_codes {
  status::multiple_choices,
  status::moved_permanently,
  status::found,
  status::see_other,
  status::not_modified,
  status::use_proxy,
  status::temporary_redirect,
  status::permanent_redirect,
};

static constexpr std::array client_error_status_codes {
  status::bad_request,
  status::unauthorized,
  status::payment_required,
  status::forbidden,
  status::not_found,
  status::method_not_allowed,
  status::not_acceptable,
  status::proxy_authentication_required,
  status::request_timeout,
  status::conflict,
  status::gone,
  status::length_required,
  status::precondition_failed,
  status::payload_too_large,
  status::request_uri_too_long,
  status::unsupported_media_type,
  status::requested_range_not_satisfiable,
  status::expectation_failed,
  status::im_a_teapot,
  status::misdirected_request,
  status::unprocessable_entity,
  status::locked,
  status::failed_dependency,
  status::upgrade_required,
  status::precondition_required,
  status::too_many_requests,
  status::request_header_fields_too_large,
  status::connection_closed_without_response,
  status::unavailable_for_legal_reasons,
  status::client_closed_request,
};

static constexpr std::array server_error_status_codes {
  status::internal,
  status::not_implemented,
  status::bad_gateway,
  status::service_unavailable,
  status::gateway_timeout,
  status::version_not_supported,
  status::variant_also_negotiates,
  status::insufficient_storage,
  status::loop_detected,
  status::not_extended,
  status::network_authentication_required,
  status::network_connect_timeout_error,
};

template <std::size_t N>
constexpr bool check_status_code (std::array<status, N> const& array, status value) {
  auto begin = array.begin();
  auto end = array.end(); 
  return std::find(begin, end, value) != end;
}

} /* nameless namespace */

namespace traffic {

std::string_view to_string (method m) noexcept {
  using namespace ::std::literals::string_view_literals;
  switch (m) {
    case method::UNKNOWN: return "UNKNOWN"sv;
    case method::CONNECT: return "CONNECT"sv;
    case method::OPTIONS: return "OPTIONS"sv;
    case method::DELETE: return "DELETE"sv;
    case method::PURGE: return "PURGE"sv;
    case method::TRACE: return "TRACE"sv;
    case method::HEAD: return "HEAD"sv;
    case method::PUSH: return "PUSH"sv;
    case method::PUT: return "PUT"sv;
    case method::GET: return "GET"sv;
  }
  return ""sv;
}

void default_delete<TSHttpParser>::operator () (pointer ptr) const noexcept {
  TSHttpParserDestroy(ptr);
}

} /* namespace traffic */

namespace traffic::http {

std::string_view header::reason () const noexcept {
  int length { 0 };
  auto text = TSHttpHdrReasonGet(this->buffer(), this->get(), std::addressof(length));
  return { text, static_cast<std::size_t>(length) };
}

std::string_view header::host () const noexcept {
  int length { 0 };
  auto text = TSHttpHdrHostGet(this->buffer(), this->get(), std::addressof(length));
  return { text, static_cast<std::size_t>(length) };
}

enum status header::status () const noexcept {
  auto value = TSHttpHdrStatusGet(this->buffer(), this->get());
  return traffic::http::status { apex::to_underlying(value) };
}

enum method header::method () const noexcept {
  int length { 0 };
  auto text = TSHttpHdrMethodGet(this->buffer(), this->get(), std::addressof(length));
  auto m = std::string_view(text, length);
  if (m == "CONNECT") { return method::CONNECT; }
  if (m == "OPTIONS") { return method::OPTIONS; }
  if (m == "DELETE") { return method::DELETE; }
  if (m == "PURGE") { return method::PURGE; }
  if (m == "TRACE") { return method::TRACE; }
  if (m == "HEAD") { return method::HEAD; }
  if (m == "PUSH") { return method::PUSH; }
  if (m == "PUT") { return method::PUT; }
  if (m == "GET") { return method::GET; }
  return method::UNKNOWN;
}

enum type header::type () const noexcept {
  auto value = TSHttpHdrTypeGet(this->buffer(), this->get());
  return traffic::http::type { apex::to_underlying(value) };
}

int header::version () const noexcept {
  return TSHttpHdrVersionGet(this->buffer(), this->get());
}

struct url header::url () const noexcept {
  TSMLoc location { };
  auto result = TSHttpHdrUrlGet(this->buffer(), this->get(), std::addressof(location));
  if (result != traffic::success) {
    // TODO: Log error, maybe make this function noexcept(false). Alternatively, use an
    // apex::outcome
  }
  return traffic::url { location, offset::deleter_type { this->buffer(), this->get() } };
}

header::size_type header::size () const noexcept {
  return TSHttpHdrLengthGet(this->buffer(), this->get());
}

parser::parser () noexcept :
  handle_type { TSHttpParserCreate() }
{ }

void parser::clear () noexcept { TSHttpParserClear(this->get()); }

bool is_informational (status value) noexcept {
  return check_status_code(::informational_status_codes, value);
}

bool is_client_error (status value) noexcept {
  return check_status_code(::client_error_status_codes, value);
}

bool is_server_error (status value) noexcept {
  return check_status_code(::server_error_status_codes, value);
}

bool is_redirection (status value) noexcept {
  return check_status_code(::redirection_status_codes, value);
}

bool is_success (status value) noexcept {
  return check_status_code(::success_status_codes, value);
}

bool is_informational (TSHttpStatus s) noexcept { return is_informational(to_status(s)); }
bool is_client_error (TSHttpStatus s) noexcept { return is_client_error(to_status(s)); }
bool is_server_error (TSHttpStatus s) noexcept { return is_server_error(to_status(s)); }
bool is_redirection(TSHttpStatus s) noexcept { return is_redirection(to_status(s)); }
bool is_success (TSHttpStatus s) noexcept { return is_success(to_status(s)); }

status to_status (TSHttpStatus s) noexcept { return status { apex::to_underlying(s) }; }

} /* namespace traffic::http */
