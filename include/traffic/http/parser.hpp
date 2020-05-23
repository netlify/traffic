#ifndef TRAFFIC_HTTP_PARSER_HPP
#define TRAFFIC_HTTP_PARSER_HPP

#include <ts/ts.h>

namespace traffic::http {

struct parser {
  using pointer = TSHttpParser;

  parser () noexcept;
  ~parser () noexcept;

  explicit operator bool () const noexcept;

  pointer get () const noexcept;

  pointer release () noexcept;
  void reset (pointer ptr = pointer { });
  void clear () noexcept;


private:
  pointer ptr;
};

} /* namespace traffic::http */

#endif /* TRAFFIC_HTTP_PARSER_HPP */
