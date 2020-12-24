#ifndef SERIAL_PORT_CONNECTOR_H
#define SERIAL_PORT_CONNECTOR_H

#include <cstdlib>

#include "s_runnable.hpp"

namespace simple {
template <typename requester_port, typename responder_port,
          typename blocking_policy>
struct port_connector : s_runnable {
  port_connector(requester_port &requester_, responder_port &responder_,
                 blocking_policy blocker_)
      : s_runnable{},
        requester{requester_},
        responder{responder_},
        blocker{blocker_} {}

  ~port_connector() {}

  virtual void run(void) override { connect(); }

 private:
  requester_port &requester;
  responder_port &responder;
  blocking_policy blocker;

 private:
  void connect(void) {
    if (requester.available_bytes() > 0) {
      std::size_t available;
      auto msg = requester.read(available);
      responder.write(msg, available);
      // most of the commands are responded in this interval
      blocker(500);
      if (responder.available_bytes() == 0) {
        // wait more for taking long response time
        blocker(2000);
      }
      if (responder.available_bytes()) {
        msg = responder.read(available);
        requester.write(msg, available);
        blocker(250);
      }
    }
  }
};
}  // namespace simple

#endif
