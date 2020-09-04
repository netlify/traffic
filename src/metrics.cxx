#include <traffic/metrics.hpp>

#include <cassert>

namespace {

auto create (char const* name, traffic::metric::persist p, TSStatSync s) {
  return TSStatCreate(name, TS_RECORDDATATYPE_INT, static_cast<TSStatPersistence>(p), s);
}

} /* nameless namespace */

namespace traffic::metric {

counter::counter (char const* name, persist p) noexcept :
  handle { ::create(name, p, TS_STAT_SYNC_COUNT) }
{ }

counter::counter (char const* name) noexcept :
  counter { name, persist::no }
{ }

counter::operator value_type () const noexcept { return this->value(); }
counter::operator bool () const noexcept { return this->has_value(); }

counter& counter::operator ++ () noexcept {
  return *this += 1;
}

counter& counter::operator += (value_type value) noexcept {
  assert(value >= 0);
  TSStatIntIncrement(this->handle, value);
  return *this;
}

counter::value_type counter::value () const noexcept {
  return TSStatIntGet(this->handle);
}

bool counter::has_value () const noexcept { return this->handle != TS_ERROR; }

void counter::clear () noexcept { TSStatIntSet(this->handle, 0); }

sum::sum (char const* name, persist p) noexcept :
  handle { ::create(name, p, TS_STAT_SYNC_SUM) }
{ }

sum::sum (char const* name) noexcept :
  sum { name, persist::no }
{ }

sum& sum::operator = (value_type value) noexcept {
  TSStatIntSet(this->handle, value);
  return *this;
}

sum::operator value_type () const noexcept { return this->value(); }
sum::operator bool () const noexcept { return this->has_value(); }

sum& sum::operator ++ () noexcept { return *this += 1; }
sum& sum::operator -- () noexcept { return *this -= 1; }

sum& sum::operator += (value_type value) noexcept {
  TSStatIntIncrement(this->handle, value);
  return *this;
}

sum& sum::operator -= (value_type value) noexcept {
  TSStatIntDecrement(this->handle, value);
  return *this;
}

sum::value_type sum::value () const noexcept { return TSStatIntGet(this->handle); }
bool sum::has_value () const noexcept { return this->handle != TS_ERROR; }

void sum::clear () noexcept { TSStatIntSet(this->handle, 0); }

average::average (char const* name, persist p) noexcept :
  handle { ::create(name, p, TS_STAT_SYNC_AVG) }
{ }

average::average (char const* name) noexcept :
  average { name, persist::no }
{ }

average& average::operator += (value_type value) noexcept {
  TSStatIntIncrement(this->handle, value);
  return *this;
}

average::operator value_type () const noexcept { return this->value(); }
average::operator bool () const noexcept { return this->has_value(); }

average::value_type average::value () const noexcept { return TSStatIntGet(this->handle); }
bool average::has_value () const noexcept { return this->handle != TS_ERROR; }

void average::clear () noexcept { TSStatIntSet(this->handle, 0); }

} /* namespace traffic::metric */
