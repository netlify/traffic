#ifndef TRAFFIC_MIME_HPP
#define TRAFFIC_MIME_HPP

#include <traffic/memory.hpp>
#include <traffic/offset.hpp>
#include <ts/ts.h>

#include <chrono>

namespace traffic {

template <> struct default_delete<TSMimeParser> {
  using pointer = TSMimeParser;
  void operator () (pointer ptr) const noexcept;
};

} /* namespace traffic */

namespace traffic::mime {

struct parser : private unique_handle<TSMimeParser> {
  parser () noexcept;

  [[clang::reinitializes]] void clear () noexcept;

  using resource_type::operator bool;
  using resource_type::get;
};

using time_point = std::chrono::system_clock::time_point;
struct field;

// XXX: A field can either hold a single value, or a list of values.
// TODO: Add constructor that takes both a 'field' and any of the values
// that can be set.
// TODO: uint64_t is actually just unsigned int
// TODO: consider having an into<T> function instead of explicit casts
struct value {
  value (field const&) noexcept;

  explicit operator std::string_view () const noexcept;
  explicit operator std::string () const;

  explicit operator std::uint64_t () const noexcept;
  explicit operator std::int64_t () const noexcept;
  explicit operator time_point () const noexcept;
  explicit operator int () const noexcept;

  value& operator = (std::string const&) noexcept;
  value& operator = (std::string_view) noexcept;
  value& operator = (std::uint64_t) noexcept;
  value& operator = (std::int64_t) noexcept;
  value& operator = (time_point) noexcept;
  value& operator = (int) noexcept;

private:
  // TODO: just store the TSMBuffer/TSMLoc/TSMLoc directly?
  TSMBuffer buffer () const noexcept;
  TSMLoc parent () const noexcept;
  TSMLoc get () const noexcept;

  field const& base;
  int idx { -1 };
};

// TODO: field requires TSMimeHdrFieldDestroy, and thus can't use the offset
// mixin. However, we're using it here to save us some time...
// TODO: Make iterable. The iterator type will just be an index and a reference
// to the field. The end iterator will most likely just be a sentinel type.
// TODO: Should this type be copyable?
struct field : offset {
  friend struct value;
  using size_type = int;

  // iterator insert (const_iterator, value const&) noexcept;

  size_type size () const noexcept;
  void clear () noexcept;
};

// TODO: Make iterable. Usable via TSMimeHdrFieldNext
struct header : private offset {
  using size_type = int;

  // iterator find (std::string_view) const noexcept;
  size_type size () const noexcept;
  void clear () noexcept;
};

} /* namespace traffic::mime */

#endif /* TRAFFIC_MIME_HPP */
