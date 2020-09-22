#include <traffic/mime.hpp>

namespace traffic {

void default_delete<TSMimeParser>::operator () (pointer ptr) const noexcept {
  TSMimeParserDestroy(ptr);
}

} /* namespace traffic */

namespace traffic::mime {

value::value (field const& base) noexcept : base(base) { }

value::operator std::string_view () const noexcept {
  int length { 0 };
  auto text = TSMimeHdrFieldValueStringGet(
    this->buffer(),
    this->parent(),
    this->get(),
    this->idx,
    std::addressof(length));
  return { text, static_cast<std::size_t>(length) };
}

value::operator std::string () const {
  return std::string { static_cast<std::string_view>(*this) };
}

value::operator std::uint64_t () const noexcept {
  return TSMimeHdrFieldValueUintGet(
    this->buffer(),
    this->parent(),
    this->get(),
    this->idx);
}

value::operator int64_t () const noexcept {
  return TSMimeHdrFieldValueInt64Get(
    this->buffer(),
    this->parent(),
    this->get(),
    this->idx);
}

value::operator time_point () const noexcept {
  return std::chrono::system_clock::from_time_t(
    TSMimeHdrFieldValueDateGet(
      this->buffer(),
      this->parent(),
      this->get()));
}

value::operator int () const noexcept {
  return TSMimeHdrFieldValueIntGet(
    this->buffer(),
    this->parent(),
    this->get(),
    this->idx);
}

value& value::operator = (int value) noexcept {
  apex::ignore = TSMimeHdrFieldValueIntSet(
    this->buffer(),
    this->parent(),
    this->get(),
    this->idx,
    value);
  return *this;
}

TSMBuffer value::buffer () const noexcept { return this->base.buffer(); }
TSMLoc value::parent () const noexcept { return this->base.parent(); }
TSMLoc value::get () const noexcept { return this->base.get(); }

field::size_type field::size () const noexcept {
  return TSMimeHdrFieldValuesCount(this->buffer(), this->parent(), this->get());
}

// TODO: log instance where TS_SUCCESS is not returned
void field::clear () noexcept {
  apex::ignore = TSMimeHdrFieldValuesClear(this->buffer(), this->parent(), this->get());
}

header::size_type header::size () const noexcept {
  return TSMimeHdrFieldsCount(this->buffer(), this->get());
}

// TODO: log instance where TS_SUCCESS is not returned~
void header::clear () noexcept {
  apex::ignore = TSMimeHdrFieldsClear(this->buffer(), this->get());
}

parser::parser () noexcept :
  resource_type { TSMimeParserCreate() }
{ }

void parser::clear () noexcept { TSMimeParserClear(this->get()); }

} /* namespace traffic::mime */
