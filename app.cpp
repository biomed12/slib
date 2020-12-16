#include "slib/s_io.hpp"
#include "slib/s_port_connector.hpp"
#include "slib/s_serial_port.hpp"

#if 0
using namespace simple;

// generic blocker
struct blocker {
  void operator()(int ms) && {
    // todo: HAL_Delay(...)
  }
};

///////////////////////////////////////////////////////VEHICLE VARIABLES

// vehicle serial port variables
struct vehicle_port_transmitter {
  void operator()(char *data, std::size_t size) noexcept {
    // todo: HAL_UART_Transmit(...)
  }
};

serial_port<vehicle_port_transmitter> vehicle_port{};

///////////////////////////////////////////////////////CAM VARIABLES

// cam serial port variables
struct cam_port_transmitter {
  void operator()(char *data, std::size_t size) noexcept {
    // todo: HAL_UART_Transmit(...)
  }
};

serial_port<cam_port_transmitter> cam_port{};

///////////////////////////////////////////////////////APP VARIABLES

// app port variables
struct app_port_transmitter {
  void operator()(char *data, std::size_t size) noexcept {
    // todo: incoming data to application goes here...
  }
};

serial_port<app_port_transmitter> app_port{};

struct app_port_receiver {
  void operator()(char *data, std::size_t size) && {
    for (std::size_t i = 0; i < size; i++) {
      app_port.push_from_ll(*(data + i));
    }
  }
};

//////////////////////////////////////////////////////PORT CONNECTORS

// vehicle <-> cam connector
port_connector<decltype(vehicle_port), 1000, decltype(cam_port), 250, blocker>
    vehicle_to_cam_connector{vehicle_port, cam_port};

// app <-> cam connector
port_connector<decltype(app_port), 1000, decltype(cam_port), 250, blocker>
    app_to_cam_connector{app_port, cam_port};

//////////////////////////////////////////////////////IOs
struct ek_io : s_io {
  bool read(void) override { return false; }

 private:
};

//
void init(void) {}
#endif
