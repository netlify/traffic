#ifndef TRAFFIC_URL_HPP
#define TRAFFIC_URL_HPP

#include <traffic/offset.hpp>
#include <string_view>

namespace traffic {

struct url : private offset {
  using offset::offset;

  std::string_view parameters () const noexcept;
  std::string_view password () const noexcept;
  std::string_view fragment () const noexcept;
  std::string_view scheme () const noexcept;
  std::string_view query () const noexcept;
  std::string_view path () const noexcept;
  std::string_view host () const noexcept;
  std::string_view user () const noexcept;

  explicit operator std::string () const;

  std::size_t size () const noexcept;
  int port () const noexcept;

  using offset::buffer;
  using offset::parent;
  using offset::get;
};

std::string to_string (url const&);

} /* namespace traffic */

#endif /* TRAFFIC_URL_HPP */
