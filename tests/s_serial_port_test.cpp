#include "slib/s_serial_port.hpp"

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"
//#include "slib/s_tick_service.hpp"

extern void global_tick(int ms);

#if 1
std::string received_data;

struct interpreter {
  void operator()(char* data, int size) noexcept {
    received_data.clear();
    for (int i = 0; i < size; i++) {
      received_data.push_back(*(data + i));
    }
  }
};

struct serial_port_test : ::testing::Test {
 protected:
  interpreter iptr;
  simple::serial_port<interpreter> port{iptr};
};

TEST_F(serial_port_test, interpreterWorksCorrect) {
  char data[] = "test";
  port.write(data, 4);
  ASSERT_EQ(std::string{"test"}, received_data);
}

auto push_data_and_make_timed_out = [](auto& port) {
  char data[] = "test";
  for (auto& e : data) {
    port.push_from_ll(e);
  }
  global_tick(50);
};

TEST_F(serial_port_test, availableByteCountEqualPushedByteCount) {
  push_data_and_make_timed_out(port);
  ASSERT_EQ(5, port.available_bytes());
}

TEST_F(serial_port_test, readDataEqualPushedData) {
  push_data_and_make_timed_out(port);
  std::size_t available{};
  ASSERT_EQ(std::string{port.read(available)}, std::string{"test"});
  ASSERT_EQ(5, available);
}

TEST_F(serial_port_test, portEmptyAfterClear) {
  push_data_and_make_timed_out(port);
  port.clear();
  std::size_t available{};
  auto ref = port.read(available);
  ASSERT_EQ(available, 0);
  ASSERT_EQ(ref, nullptr);
}

TEST(non_fixture_serial_port_test, snifferSniffs) {
  struct sniffer_transmitter {
    void operator()(char* data, int size) {
      (void)data;
      (void)size;
    }
  };
  static sniffer_transmitter trs;

  static std::string sniffing_data{};
  struct sniffible_port : simple::serial_port<sniffer_transmitter> {
    sniffible_port() : simple::serial_port<sniffer_transmitter>{trs} {}
    void reading_sniffer(char* data, int size) {
      char* buffer = new char[size + 1]{};
      std::copy(data, data, buffer);
      sniffing_data.clear();
      sniffing_data = std::string{buffer};
    }
  };

  sniffible_port ins;

  push_data_and_make_timed_out(ins);
}
#endif
