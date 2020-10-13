#include <traffic/uuid.hpp>
#include <cstring>

namespace traffic {

void default_delete<TSUuid>::operator () (pointer ptr) const noexcept {
  TSUuidDestroy(ptr);
}

uuid::uuid () noexcept :
  resource_type(TSUuidCreate())
{ this->regenerate(); }

apex::optional<uuid> uuid::parse (std::string const& str) noexcept { return uuid::parse(str.data()); }
apex::optional<uuid> uuid::parse (apex::zstring_view str) noexcept { return uuid::parse(str.data()); }
apex::optional<uuid> uuid::parse (char const* str) noexcept {
  auto ptr = TSUuidCreate();
  auto result = TSUuidStringParse(ptr, str);
  if (result == TS_SUCCESS) { return uuid(ptr); }
  TSUuidDestroy(ptr);
  return std::nullopt;
}

void uuid::regenerate () noexcept {
  if (TS_SUCCESS != TSUuidInitialize(this->get(), TS_UUID_V4)) {
    /* TODO: Log this as an 'error' (though we of course can't figure out *why*
     * it's an error because TrafficServer 🙄)
     */
  }
}

char const* uuid::data () const noexcept { return TSUuidStringGet(this->get()); }
size_t uuid::size () const noexcept { return strlen(this->data()); }

apex::zstring_view to_string_view (uuid value) noexcept { return value.data(); }
std::string to_string (uuid value) { return value.data(); }

} /* namespace traffic */
