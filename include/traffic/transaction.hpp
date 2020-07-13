#ifndef TRAFFIC_TRANSACTION_HPP
#define TRAFFIC_TRANSACTION_HPP

#include <traffic/session.hpp>
#include <traffic/http.hpp>
#include <ts/ts.h>

namespace traffic {

struct transaction : private view_handle<TSHttpTxn> {

  using handle_type::handle_type;
  using handle_type::get;

  http::header cached_response () const noexcept;
  http::header cached_request () const noexcept;

  http::header server_response () const noexcept;
  http::header server_request () const noexcept;

  http::header response () const noexcept;
  http::header request () const noexcept;

  [[nodiscard]] traffic::session session () const noexcept;
  [[nodiscard]] std::string_view tag () const noexcept;

  [[nodiscard]] bool websocket () const noexcept;
  [[nodiscard]] bool internal () const noexcept;
  [[nodiscard]] bool aborted () const noexcept;

  [[nodiscard]] bool debug () const noexcept;

  void mark (int) noexcept;
  void dscp (int) noexcept;

//  [[nodiscard]] url cache_lookup_url () const noexcept;
};

} /* namespace traffic */

#endif /* TRAFFIC_TRANSACTION_HPP */
