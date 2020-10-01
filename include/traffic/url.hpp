#ifndef TRAFFIC_URL_HPP
#define TRAFFIC_URL_HPP

#include <traffic/offset.hpp>
#include <string_view>

namespace traffic {

struct url : private offset {
  using pointer = typename offset::pointer;
  url (pointer, TSMBuffer, pointer) noexcept;
  url (pointer, TSMBuffer) noexcept;

  [[nodiscard]] std::string_view parameters () const noexcept;
  [[nodiscard]] std::string_view password () const noexcept;
  [[nodiscard]] std::string_view fragment () const noexcept;
  [[nodiscard]] std::string_view scheme () const noexcept;
  [[nodiscard]] std::string_view query () const noexcept;
  [[nodiscard]] std::string_view path () const noexcept;
  [[nodiscard]] std::string_view host () const noexcept;
  [[nodiscard]] std::string_view user () const noexcept;
  [[nodiscard]] int port () const noexcept;

  void parameters (std::string_view) noexcept;
  void password (std::string_view) noexcept;
  void fragment (std::string_view) noexcept;
  void scheme (std::string_view) noexcept;
  void query (std::string_view) noexcept;
  void path (std::string_view) noexcept;
  void host (std::string_view) noexcept;
  void user (std::string_view) noexcept;
  void port (int) noexcept;

  [[nodiscard]] std::size_t size () const noexcept;
  [[nodiscard]] bool empty () const noexcept;

  using offset::buffer;
  using offset::parent;
  using offset::get;
};

std::string to_string (url const&);

} /* namespace traffic */

#endif /* TRAFFIC_URL_HPP */
