#ifndef TRAFFIC_PLUGIN_HPP
#define TRAFFIC_PLUGIN_HPP

namespace traffic {

enum class hook {
  read_request_headers_pre_remap,
  read_request_headers_post_remap,
  send_request_headers,
  read_response_headers,
  send_response_headers,
  os_dns,
  read_request_headers,
  read_cache_headers,
  cache_lookup_complete,
  select_alt,
};

} /* namespace traffic */

#endif /* TRAFFIC_PLUGIN_HPP */
