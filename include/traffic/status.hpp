#ifndef TRAFFIC_STATUS_HPP
#define TRAFFIC_STATUS_HPP

#include <ts/ts.h>

namespace traffic {

enum class status {
  success = TS_SUCCESS,
  error = TS_ERROR,
};

} /* namespace traffic */

#endif /* TRAFFIC_STATUS_HPP */
