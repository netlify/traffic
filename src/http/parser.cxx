#include <traffic/http/parser.hpp>

namespace traffic::http {

parser::parser () noexcept : ptr { TSHttpParserCreate() } { }
parser::~parser () noexcept {
  if (*this) { TSHttpParserDestroy(this->get()); }
}

parser::operator bool () const noexcept { return this->get(); }

parser::pointer parser::get () const noexcept { return this->ptr; }

void parser::clear () noexcept { TSHttpParserClear(this->get()); }

} /* namespace traffic::http */
