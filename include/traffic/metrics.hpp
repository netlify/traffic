#ifndef TRAFFIC_METRICS_HPP
#define TRAFFIC_METRICS_HPP

#include <ts/ts.h>

namespace traffic::metric {

enum class persist {
  yes = TS_STAT_PERSISTENT,
  no = TS_STAT_NON_PERSISTENT
};

struct counter {
  using value_type = TSMgmtInt;

  counter (counter const&) = delete;
  counter () = delete;

  counter& operator = (counter const&) = delete;

  counter (char const*, persist) noexcept;
  counter (char const*) noexcept;

  explicit operator value_type () const noexcept;
  explicit operator bool () const noexcept;

  counter& operator += (value_type) noexcept;

  counter& operator ++ () noexcept;

  value_type value () const noexcept;
  bool has_value () const noexcept;

  void clear () noexcept;

private:
  int handle { };
};

struct sum {
  using value_type = TSMgmtInt;

  sum (sum const&) = delete;
  sum () = delete;

  sum& operator = (sum const&) = delete;

  sum (char const*, persist) noexcept;
  sum (char const*) noexcept;

  sum& operator = (value_type) noexcept;

  explicit operator value_type () const noexcept;
  explicit operator bool () const noexcept;

  sum& operator += (value_type) noexcept;
  sum& operator -= (value_type) noexcept;

  sum& operator ++ () noexcept;
  sum& operator -- () noexcept;

  value_type value () const noexcept;
  bool has_value () const noexcept;

  void clear () noexcept;

private:
  int handle { };
};

struct average {
  using value_type = TSMgmtInt;

  average (average const&) = delete;
  average () = delete;

  average& operator = (average const&) = delete;

  average (char const*, persist) noexcept;
  average (char const*) noexcept;

  explicit operator value_type () const noexcept;
  explicit operator bool () const noexcept;

  average& operator += (value_type) noexcept;

  value_type value () const noexcept;
  bool has_value () const noexcept;

  void clear () noexcept;

private:
  int handle { };
};

} /* namespace traffic::metric */

#endif /* TRAFFIC_METRICS_HPP */
