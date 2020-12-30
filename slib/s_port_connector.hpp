#ifndef SERIAL_PORT_CONNECTOR_H
#define SERIAL_PORT_CONNECTOR_H

#include <cstdlib>

#include "s_runnable.hpp"
#include "utils/debugger.h"

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
  void connect(bool clear_flag = true) {
    if (requester.available_bytes() > 0) {
      debugger("%d byte istek gonderildi...\r", requester.available_bytes());
      std::size_t available;
      auto msg = requester.read(available);
      responder.write(msg, available);
      if (clear_flag) requester.clear();
      // most of the commands are responded in this interval
      debugger("cevap bekleniyor...\r");
    } else {
      /*Istek yapilmadan cevap mevcutsa, ilk acilis vs. direkt gonder...*/
      if (responder.available_bytes()) {
        std::size_t available{0};
        auto msg = responder.read(available);
        requester.write(msg, available);
        responder.clear();
      }
    }
  }
};
}  // namespace simple

#endif
