#ifndef TRAFFIC_UUID_HPP
#define TRAFFIC_UUID_HPP

#include <apex/core/optional.hpp>
#include <apex/core/string.hpp>
#include <traffic/memory.hpp>
#include <ts/ts.h>

namespace traffic {

template <> struct default_delete<TSUuid> {
  using pointer = TSUuid;
  void operator () (pointer) const noexcept;
};

struct uuid : private unique_handle<TSUuid> {

  static apex::optional<uuid> parse (std::string const&) noexcept;
  static apex::optional<uuid> parse (apex::zstring_view) noexcept;
  static apex::optional<uuid> parse (char const*) noexcept;

  using resource_type::resource_type;
  using resource_type::operator bool;
  using resource_type::get;

  char const* data () const noexcept;
  size_t size () const noexcept; /* O(n) operation */
};

apex::zstring_view to_string_view (uuid) noexcept;
std::string to_string (uuid);

} /* namespace traffic */

#endif /* TRAFFIC_UUID_HPP */
