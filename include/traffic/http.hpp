#ifndef TRAFFIC_HTTP_HPP
#define TRAFFIC_HTTP_HPP

#include <traffic/constants.hpp>
#include <traffic/memory.hpp>
#include <traffic/buffer.hpp>
#include <traffic/offset.hpp>
#include <traffic/url.hpp>
#include <ts/ts.h>

#include <string_view>

namespace traffic {

template <> struct default_delete<TSHttpParser> {
  using pointer = TSHttpParser;

  void operator () (pointer) const noexcept;
};

struct buffer;

} /* namespace traffic */

namespace traffic::http {

struct alternative_selection final : private view_handle<TSHttpAltInfo> {
  using resource_type::resource_type;
  using resource_type::get;
  void operator = (apex::convertible_to<int> auto) = delete;
  void operator = (float quality) noexcept;
};

std::string_view to_string (method) noexcept;

struct header : private offset {
  using offset::offset;
  using size_type = int;

  std::string_view reason () const noexcept;
  std::string_view host () const noexcept;

  traffic::url url () const noexcept;

  enum status status () const noexcept;
  enum method method () const noexcept;
  enum type type () const noexcept;
  int version () const noexcept;

  size_type size () const noexcept;
};
// TSHttpHdrPrint writes to an io::buffer. It should be added at some point

// This is sitting in the public API until stable :)
struct parser_sentinel;
struct parser_iterator;

// This is an 'iterable' type. We hide the 'result' code of TS_PARSE_DONE.
// As long as the 'current' returned code is TS_PARSE_CONT, we are able to be
// iterated. This result code is simply stored in the begin() iterator. When
// comparing against the sentinel type, we simply check if the code is
// TS_PARSE_DONE.
// On operator *() const, if the result code was TS_PARSE_ERROR, we *could*
// throw an exception. However this kind of breaks a lot of expected behavior
// out there, and ideally we would like all iterators to be noexcept.
// We'll have to try out both forms.
// before we consider this type stable, we should move the iterator into an impl
// namespace, because the iterator itself should *not* be accessible to the
// general public.
// Of note, we need to 'select' whether we are parsing a request or a response.
// This, of course, matters a great deal
struct parser : private unique_handle<TSHttpParser> {
  parser () noexcept;

  [[clang::reinitializes]] void clear () noexcept;

  using resource_type::operator bool;
  using resource_type::get;
};

bool is_informational (status) noexcept;
bool is_client_error (status) noexcept;
bool is_server_error (status) noexcept;
bool is_redirection(status) noexcept;
bool is_success (status) noexcept;

bool is_informational (TSHttpStatus) noexcept;
bool is_client_error (TSHttpStatus) noexcept;
bool is_server_error (TSHttpStatus) noexcept;
bool is_redirection(TSHttpStatus) noexcept;
bool is_success (TSHttpStatus) noexcept;

status to_status (TSHttpStatus) noexcept;

std::string_view to_reason (TSHttpStatus) noexcept; // TSHttpHdrReasonLookup
std::string_view to_string (method) noexcept;

} /* namespace traffic::http */

#endif /* TRAFFIC_HTTP_HPP */
