#include <traffic/mime.hpp>

namespace traffic {

void default_delete<TSMimeParser>::operator () (pointer ptr) const noexcept {
  TSMimeParserDestroy(ptr);
}

} /* namespace traffic */

namespace traffic::mime {

parser::parser () noexcept :
  handle_type { TSMimeParserCreate() }
{ }

void parser::clear () noexcept { TSMimeParserClear(this->get()); }

} /* namespace traffic::mime */
