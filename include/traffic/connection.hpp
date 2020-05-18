#ifndef TRAFFIC_CONNECTION_HPP
#define TRAFFIC_CONNECTION_HPP

#include <ts/ts.h>

namespace traffic {

struct connection final {
  static connection client (TSHttpSsn) noexcept;
  static connection server (TSHttpSsn) noexcept;

  bool is_ssl () const noexcept;
private:
};

} /* namespace traffic */

#endif /* TRAFFIC_CONNECTION_HPP */
