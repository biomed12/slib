#include "slib/s_io.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern void global_tick(int ms);

#if 1
using namespace simple;

struct mock_io : s_io {
  mock_io(int th = 100) : s_io{th} {}
  MOCK_METHOD(bool, read, (), (override));
  MOCK_METHOD(void, raising_edge_handler, (), (override));
  MOCK_METHOD(void, falling_edge_handler, (), (override));
};

void tick_during_5sec(void) {
  for (int i = 0; i < 50; i++) {
    global_tick(10);
  }
}

TEST(mock_io_test, initialActionIsTakenOnce) {
  mock_io io;

  EXPECT_CALL(io, falling_edge_handler()).Times(1);
  EXPECT_CALL(io, read())
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(::testing::Return(false));

  tick_during_5sec();
}

TEST(mock_io_test, justInitialActionIsTakenWhenInputDoesNotChange) {
  // Input is accepted false initially by the library
  mock_io io;
  EXPECT_CALL(io, read())
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(::testing::Return(false));

  EXPECT_CALL(io, raising_edge_handler()).Times(0);
  EXPECT_CALL(io, falling_edge_handler()).Times(1);
  tick_during_5sec();
}

TEST(mock_io_test, initialActionIsTakenEvenIfInitialVoltageIsHigh) {
  mock_io io;
  EXPECT_CALL(io, read())
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(::testing::Return(true));

  EXPECT_CALL(io, raising_edge_handler()).Times(1);
  EXPECT_CALL(io, falling_edge_handler()).Times(0);
  tick_during_5sec();
}

TEST(mock_io_test, raisingEdgeIsDetected) {
  mock_io io;

  EXPECT_CALL(io, read()).Times(::testing::AtLeast(1));

  tick_during_5sec();

  EXPECT_CALL(io, read())
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(io, raising_edge_handler()).Times(1);
  tick_during_5sec();
}

TEST(mock_io_test, fallingEdgeDetectedAfterRisingEdge) {
  mock_io io;

  EXPECT_CALL(io, read())
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(::testing::Return(true));
  tick_during_5sec();

  EXPECT_CALL(io, read())
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(io, falling_edge_handler()).Times(1);
  tick_during_5sec();
}
#endif
