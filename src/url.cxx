#include <traffic/url.hpp>

#include <apex/core/scope.hpp>
#include <functional>

namespace {

using extract_function_type = auto(*)(TSMBuffer, TSMLoc, int*) -> char const*;

std::string_view extract(extract_function_type fn, traffic::url const& url) {
  int length { 0 };
  auto text = std::invoke(fn, url.buffer(), url.get(), std::addressof(length));
  return { text, static_cast<std::size_t>(length) };
}

} /* nameless namespace */

namespace traffic {

std::string_view url::parameters () const noexcept { return ::extract(TSUrlHttpParamsGet, *this); }
std::string_view url::password () const noexcept { return ::extract(TSUrlPasswordGet, *this); }
std::string_view url::fragment () const noexcept { return ::extract(TSUrlHttpFragmentGet, *this); }
std::string_view url::scheme () const noexcept { return ::extract(TSUrlSchemeGet, *this); }
std::string_view url::query () const noexcept { return ::extract(TSUrlHttpQueryGet, *this); }
std::string_view url::path () const noexcept { return ::extract(TSUrlPathGet, *this); }
std::string_view url::host () const noexcept { return ::extract(TSUrlHostGet, *this); }
std::string_view url::user () const noexcept { return ::extract(TSUrlUserGet, *this); }

url::operator std::string () const {
  int length { 0 };
  auto text = TSUrlStringGet(this->buffer(), this->get(), std::addressof(length));
  apex::scope_exit exit { [=] { TSfree(text); } };
  return { text, static_cast<std::size_t>(length) };
}

std::size_t url::size () const noexcept { return TSUrlLengthGet(this->buffer(), this->get()); }
int url::port () const noexcept { return TSUrlPortGet(this->buffer(), this->get()); }

std::string to_string (url const& u) {
  return static_cast<std::string>(u);
}

} /* namespace traffic */
