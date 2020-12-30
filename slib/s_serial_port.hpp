#ifndef SIMPLE_SERIAL_PORT_H
#define SIMPLE_SERIAL_PORT_H

#include <algorithm>
#include <array>
#include <cstdlib>

#include "s_timer.hpp"

namespace simple {
template <typename transmitter_policy>
struct serial_port {
  serial_port(transmitter_policy transmitter_, unsigned int rx_timeout = 50)
      : timer{rx_timeout},
        rx_buffer{},
        rx_counter{},
        transmitter{transmitter_} {

        };

  ~serial_port() {}

  void write(char *data, std::size_t size) noexcept {
    transmitter(data, size);
  };

  virtual void reading_sniffer(char *data, int size) {}

  std::size_t available_bytes(void) const noexcept {
    if (timer.is_timeout() == false) {
      return 0;
    }

    return rx_counter;
  }

  char *read(std::size_t &available) noexcept {
    char *ref{nullptr};
    available = 0;

    if (timer.is_timeout() == false) {
      return ref;
    }

    if (rx_counter == 0) {
      return ref;
    }

    available = rx_counter;
    ref = rx_buffer.data();

    reading_sniffer(ref, available);
    return ref;
  }

  void clear(void) noexcept { rx_counter = 0; }

  template <typename T>
  void push_from_ll(T &&data) noexcept {
    if (rx_counter < rx_buffer.size()) {
      rx_buffer[rx_counter] = data;
      rx_counter++;
      timer.reset();
    } else {
      // todo:
    }
  };

 protected:
  simple::timer timer;
  std::array<char, 64> rx_buffer;
  std::size_t rx_counter;
  transmitter_policy transmitter;
};
}  // namespace simple

#endif
