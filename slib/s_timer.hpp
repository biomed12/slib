#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include <cstdlib>

#include "s_tickable.hpp"

namespace simple {
struct timer : s_tickable {
  timer(std::size_t interval_ = 50) noexcept
      : interval{interval_}, counter{0} {}
  ~timer() noexcept {}
  auto get_value() const noexcept { return counter; }
  auto get_interval(void) const noexcept { return interval; }
  auto set_interval(std::size_t interval_) noexcept { interval = interval_; };
  auto is_timeout(void) const noexcept { return (counter >= interval); }
  auto reset(void) noexcept { counter = 0; }
  void tick(int ms) override {
    if (counter < interval) {
      counter += ms;
    }
  };

 private:
  std::size_t interval;
  volatile std::size_t counter;
};

}  // namespace simple

#endif
