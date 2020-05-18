#ifndef TRAFFIC_LOCATION_HPP
#define TRAFFIC_LOCATION_HPP

namespace traffic {

template <class T>
struct default_delete {
  void operator () (T*) const noexcept;
};

struct default_delete<TSMLoc> {
  using pointer = TSMLoc;
  void operator () (pointer) const noexcept;
};

struct location {
private:
  std::unique_ptr<TSMLoc, default_delete<TSMLoc>> handle
};

} /* namespace traffic */

#endif /* TRAFFIC_LOCATION_HPP */
