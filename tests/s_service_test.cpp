#include "slib/s_service.hpp"

#include "gtest/gtest.h"

#if 0
struct subscriber {
  void algo() { is_algo_done = true; }
  bool is_algo_done{false};
};

using namespace simple;

struct s_service_test : ::testing::Test {
  void TearDown() override { service.clear(); }

 protected:
  s_service<subscriber, 10> service;
};

TEST_F(s_service_test, initialyHasZeroSubscribers) {
  ASSERT_EQ(0, service.available_subscribers());
}

TEST_F(s_service_test, hasOneSubscriber) {
  subscriber sb;
  service.subscribe(sb);
  ASSERT_EQ(1, service.available_subscribers());
}

TEST_F(s_service_test, hasManySubscribers) {
  subscriber sb1;
  subscriber sb2;
  service.subscribe(sb1);
  service.subscribe(&sb2);
  ASSERT_EQ(2, service.available_subscribers());
}

TEST_F(s_service_test, serves) {
  subscriber sb1;
  subscriber sb2;
  service.subscribe(sb1);
  service.subscribe(&sb2);
  ASSERT_NE(true, sb1.is_algo_done);
  ASSERT_NE(true, sb2.is_algo_done);
  service.serv([](auto&& e) { e->algo(); });
  ASSERT_EQ(true, sb1.is_algo_done);
  ASSERT_EQ(true, sb2.is_algo_done);
}
#endif
