#ifndef TRAFFIC_EVENT_HPP
#define TRAFFIC_EVENT_HPP

#include <ts/apidefs.h>

namespace traffic {

// TODO: break up these events for different categories, e.g., general, vconn, etc.

enum class event {
  none = TS_EVENT_NONE,
  error = TS_EVENT_ERROR,
  immediate = TS_EVENT_IMMEDIATE,
  timeout = TS_EVENT_TIMEOUT,
  resume = TS_EVENT_CONTINUE,
  vconn_read_ready = TS_EVENT_VCONN_READ_READY,
  vconn_write_ready = TS_EVENT_VCONN_WRITE_READY,
  vconn_read_complete = TS_EVENT_VCONN_READ_COMPLETE,
  vconn_write_complete = TS_EVENT_VCONN_WRITE_COMPLETE,
  vconn_eos = TS_EVENT_VCONN_EOS,
  vconn_inactivity_timeout = TS_EVENT_VCONN_INACTIVITY_TIMEOUT,
  vconn_active_timeout = TS_EVENT_VCONN_ACTIVE_TIMEOUT,
  vconn_start = TS_EVENT_VCONN_START,
  vconn_close = TS_EVENT_VCONN_CLOSE,
  outbound_start = TS_EVENT_VCONN_START,
  outbound_close = TS_EVENT_VCONN_CLOSE,
  net_connect = TS_EVENT_NET_CONNECT,
  net_connect_failed = TS_EVENT_NET_CONNECT_FAILED,
  net_accept = TS_EVENT_NET_ACCEPT,
  net_accept_failed = TS_EVENT_NET_ACCEPT_FAILED,
  cache_open_read_failed = TS_EVENT_CACHE_OPEN_READ_FAILED,
  cache_open_write = TS_EVENT_CACHE_OPEN_WRITE,
  cache_open_write_failed = TS_EVENT_CACHE_OPEN_WRITE_FAILED,
  cache_remove = TS_EVENT_CACHE_REMOVE,
  cache_remove_failed = TS_EVENT_CACHE_REMOVE_FAILED,
  cache_scan = TS_EVENT_CACHE_SCAN,
  cache_scan_failed = TS_EVENT_CACHE_SCAN_FAILED,
  cache_scan_object = TS_EVENT_CACHE_SCAN_OBJECT,
  cache_scan_operation_blocked = TS_EVENT_CACHE_SCAN_OPERATION_BLOCKED,
  cache_scan_operation_failed = TS_EVENT_CACHE_SCAN_OPERATION_FAILED,
  cache_scan_done = TS_EVENT_CACHE_SCAN_DONE,
  cache_lookup = TS_EVENT_CACHE_LOOKUP,
  cache_read = TS_EVENT_CACHE_READ,
  cache_delete = TS_EVENT_CACHE_DELETE,
  cache_write = TS_EVENT_CACHE_WRITE,
  cache_write_header = TS_EVENT_CACHE_WRITE_HEADER,
  cache_close = TS_EVENT_CACHE_CLOSE,
  cache_lookup_ready = TS_EVENT_CACHE_LOOKUP_READY,
  cache_lookup_complete = TS_EVENT_CACHE_LOOKUP_COMPLETE,
  cache_read_ready = TS_EVENT_CACHE_READ_READY,
  cache_read_complete = TS_EVENT_CACHE_READ_COMPLETE,
};

} /* namespace traffic */

#endif /* TRAFFIC_EVENT_HPP */
