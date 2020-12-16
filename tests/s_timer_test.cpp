#include "slib/s_timer.hpp"

#include <iostream>

#include "gtest/gtest.h"

#if 0

struct simple_timer_f : ::testing::Test {
  simple_timer_f() : t{} {}

  void SetUp() override {}
  void TearDown() override {}

 protected:
  simple::timer t;
};

TEST_F(simple_timer_f, initialInvervalIs50Ms) {
  ASSERT_EQ(t.get_interval(), 50);
}

TEST_F(simple_timer_f, intervalSetCorrect) {
  t.set_interval(10);
  ASSERT_EQ(t.get_interval(), 10);
}

TEST_F(simple_timer_f, notTimedoutAtBegining) { ASSERT_FALSE(t.is_timeout()); }

extern void global_tick(int ms);

TEST_F(simple_timer_f, doesNotOverflow) {
  for (unsigned int i = 0; i < 10; i++) {
    global_tick(10);
    ASSERT_LE(t.get_value(), t.get_interval());
  }
}

TEST_F(simple_timer_f, valueIsZeroAtBegining) { ASSERT_EQ(t.get_value(), 0); }

TEST_F(simple_timer_f, valuePerTickIsCorrect) {
  for (unsigned int i = 1; i <= 5; i++) {
    global_tick(10);
    ASSERT_EQ((i * 10), t.get_value());
  }
}

static void make_timeout(simple::timer& t) {
  while (t.get_value() < t.get_interval()) {
    global_tick(10);
  }
}

TEST_F(simple_timer_f, timeoutsAtInverval) {
  make_timeout(t);
  ASSERT_TRUE(t.is_timeout() == true);
}

TEST_F(simple_timer_f, doesntNotCountAfterTimeout) {
  make_timeout(t);
  global_tick(10);
  ASSERT_EQ(t.get_interval(), t.get_value());
}
#endif
