#include "slib/s_port_connector.hpp"

#include "gtest/gtest.h"
#include "slib/s_serial_port.hpp"
#include "utils/debugger.h"

#ifdef DEBUGGER
template <typename... Args>
void debugger(Args... args) {}
#endif

template <typename... Args>
void debugger(Args... args) {}

extern void global_tick(int ms);
extern void global_runner(void);

#if 1
using namespace simple;

std::string request;
std::string response;

// request yapan portun transmitter'i
struct requester_transmitter {
  void operator()(char* data, int size) {
    // requester port'a response'un gonderilmesi beklenir
    response.clear();
    for (int i = 0; i < size; i++) {
      response.push_back(*(data + i));
    }
  }
};

// response veren portun transmitter'i
struct responder_transmitter {
  void operator()(char* data, int size) {
    // responder port'a request'in gonderilmesi beklenir
    request.clear();
    for (int i = 0; i < size; i++) {
      request.push_back(*(data + i));
    }
  }
};

struct blocker {
  void operator()(int ms) {}
} blocker_insance;

serial_port requester{[](char* data, int size) {
  // requester port'a response'un gonderilmesi beklenir
  response.clear();
  for (int i = 0; i < size; i++) {
    response.push_back(*(data + i));
  }
}};

serial_port responder{[](char* data, int size) {
  // responder port'a request'in gonderilmesi beklenir
  request.clear();
  for (int i = 0; i < size; i++) {
    request.push_back(*(data + i));
  }
}};

struct s_port_connector_test : ::testing::Test {
  s_port_connector_test() : connector{requester, responder, blocker_insance} {}

 protected:
  port_connector<decltype(requester), decltype(responder), blocker> connector;
};

auto push_message_and_make_timeout = [](auto& port, std::string msg) {
  for (auto& e : msg) {
    port.push_from_ll(e);
  }
  global_tick(100);
};

TEST_F(s_port_connector_test, dataFromRequesterSideIsAvailableAtResponder) {
  push_message_and_make_timeout(requester, "request message");
  global_runner();
  global_runner();
  ASSERT_EQ(request, std::string{"request message"});
}

TEST_F(s_port_connector_test, dataFromResponderSideIsAvailableAtRequester) {
  push_message_and_make_timeout(requester, "request message");
  push_message_and_make_timeout(responder, "response message");
  global_runner();
  global_runner();
  ASSERT_EQ(response, std::string{"response message"});
}
#endif
