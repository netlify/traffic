#ifndef TRAFFIC_TRANSACTION_HPP
#define TRAFFIC_TRANSACTION_HPP

#include <ts/ts.h>

namespace traffic {

struct transaction {
  using pointer = TSHttpTxn;

  bool is_websocket () const noexcept;
  bool is_internal () const noexcept;
  bool is_aborted () const noexcept;

  pointer get () const noexcept;

private:
  pointer handle;
};

} /* namespace traffic */

#endif /* TRAFFIC_TRANSACTION_HPP */
