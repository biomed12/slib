#ifndef SIMPLE_SERIAL_PORT_H
#define SIMPLE_SERIAL_PORT_H

#include <algorithm>
#include <array>
#include <cstdlib>

#include "s_timer.hpp"

namespace simple {
template <typename port_transmitter>
struct serial_port {
  serial_port(unsigned int rx_timeout = 50)
      : timer{rx_timeout},
        rx_buffer{},
        rx_counter{} {

        };

  ~serial_port() {}

  void write(char *data, std::size_t size) noexcept {
    transmitter(data, size);
  };

  virtual void reading_sniffer(char *data, int size) {}

  std::size_t available_bytes(void) const noexcept { return rx_counter; }
  char *read(std::size_t &available) noexcept {
    char *ref{nullptr};
    available = 0;

    if (timer.is_timeout() == false) {
      return ref;
    }

    if (rx_counter != 0) {
      available = rx_counter;
      ref = rx_buffer.data();
    }

    reading_sniffer(ref, available);
    return ref;
  }

  void clear(void) noexcept { rx_counter = 0; }

  void push_from_ll(char &data) noexcept {
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
  std::array<char, 1024> rx_buffer;
  std::size_t rx_counter;
  port_transmitter transmitter;
};
}  // namespace simple

#endif