#include <traffic/url.hpp>

#include <apex/core/scope.hpp>
#include <functional>

namespace {

using extract_function_type = auto(*)(TSMBuffer, TSMLoc, int*) -> char const*;
using insert_function_type = auto(*)(TSMBuffer, TSMLoc, char const*, int) -> TSReturnCode;

std::string_view extract(extract_function_type fn, traffic::url const& url) {
  int length { 0 };
  auto text = fn(url.buffer(), url.get(), std::addressof(length));
  return { text, static_cast<std::size_t>(length) };
}

void insert(insert_function_type fn, traffic::url const& url, char const* str,  std::size_t len) {
  auto length = static_cast<int>(len);
  auto result = fn(url.buffer(), url.get(), str, length);
  if (result != TS_SUCCESS) {
    TSDebug("netlify.traffic.internals", "Unable to set URL subproperty with value '%.*s'", length, str);
  }
}

} /* nameless namespace */

namespace traffic {

url::url (pointer ptr, TSMBuffer buffer, pointer base) noexcept :
  offset(ptr, offset::deleter_type(buffer, base))
{ }

url::url (pointer ptr, TSMBuffer buffer) noexcept :
  offset(ptr, offset::deleter_type(buffer))
{ }

std::string_view url::parameters () const noexcept { return ::extract(TSUrlHttpParamsGet, *this); }
std::string_view url::password () const noexcept { return ::extract(TSUrlPasswordGet, *this); }
std::string_view url::fragment () const noexcept { return ::extract(TSUrlHttpFragmentGet, *this); }
std::string_view url::scheme () const noexcept { return ::extract(TSUrlSchemeGet, *this); }
std::string_view url::query () const noexcept { return ::extract(TSUrlHttpQueryGet, *this); }
std::string_view url::path () const noexcept { return ::extract(TSUrlPathGet, *this); }
std::string_view url::host () const noexcept { return ::extract(TSUrlHostGet, *this); }
std::string_view url::user () const noexcept { return ::extract(TSUrlUserGet, *this); }
int url::port () const noexcept { return TSUrlPortGet(this->buffer(), this->get()); }

void url::parameters (std::string_view value) noexcept {
  ::insert(TSUrlHttpParamsSet, *this, value.data(), value.size());
}

void url::password (std::string_view value) noexcept {
  ::insert(TSUrlPasswordSet, *this, value.data(), value.size());
}

void url::fragment (std::string_view value) noexcept {
  ::insert(TSUrlHttpFragmentSet, *this, value.data(), value.size());
}

void url::scheme (std::string_view value) noexcept {
  ::insert(TSUrlSchemeSet, *this, value.data(), value.size());
}

void url::query (std::string_view value) noexcept {
  ::insert(TSUrlHttpQuerySet, *this, value.data(), value.size());
}

void url::path (std::string_view value) noexcept {
  ::insert(TSUrlPathSet, *this, value.data(), value.size());
}

void url::host (std::string_view value) noexcept {
  ::insert(TSUrlHostSet, *this, value.data(), value.size());
}

void url::user (std::string_view value) noexcept {
  ::insert(TSUrlUserSet, *this, value.data(), value.size());
}

void url::port (int value) noexcept {
  auto result = TSUrlPortSet(this->buffer(), this->get(), value);
  if (result != TS_SUCCESS) {
    TSDebug("netlify.traffic.internals", "Could not set URL port to %d", value);
  }
}

std::size_t url::size () const noexcept { return TSUrlLengthGet(this->buffer(), this->get()); }
bool url::empty () const noexcept { return this->size() == 0; }

std::string to_string (url const& u) {
  int length { 0 };
  auto text = TSUrlStringGet(u.buffer(), u.get(), std::addressof(length));
  apex::scope_exit exit { [=] { TSfree(text); } };
  return { text, static_cast<std::size_t>(length) };
}

} /* namespace traffic */
