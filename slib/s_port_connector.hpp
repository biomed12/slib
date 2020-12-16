#ifndef SERIAL_PORT_CONNECTOR_H
#define SERIAL_PORT_CONNECTOR_H

#include <cstdlib>

#include "s_runnable.hpp"

namespace simple {
template <typename requester_port, std::size_t post_request_blocking_time,
          typename responder_port, std::size_t post_response_blocking_time,
          typename blocker>
struct port_connector : s_runnable {
  port_connector(requester_port &requester_, responder_port &responder_)
      : s_runnable{}, requester{requester_}, responder{responder_} {}

  ~port_connector() {}

  virtual void run(void) override { connect(); }

 private:
  requester_port &requester;
  responder_port &responder;

 private:
  void connect(void) {
    if (requester.available_bytes() > 0) {
      std::size_t available;
      auto msg = requester.read(available);
      responder.write(msg, available);
      blocker{}(post_request_blocking_time);
      if (responder.available_bytes()) {
        msg = responder.read(available);
        requester.write(msg, available);
        blocker{}(post_response_blocking_time);
      }
    }
  }
};
}  // namespace simple

#endif
