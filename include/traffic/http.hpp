#ifndef TRAFFIC_HTTP_HPP
#define TRAFFIC_HTTP_HPP

namespace traffic::http {

enum class status {
  ok = 200,
  created = 201,
  accepted = 202,
  non_authoritative_information = 203,
  no_content = 204,
  reset_content = 205,
  partial_content = 206,
  multi_status = 207,
  already_reported = 208,
  im_used = 211,
};

} /* namespace traffic::http */

#endif /* TRAFFIC_HTTP_HPP */
