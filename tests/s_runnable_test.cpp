#include "slib/s_runnable.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern void global_runner(void);

using namespace simple;

#if 0

struct runnable_mock : s_runnable {
  MOCK_METHOD(void, run, (), (override));
};

TEST(s_runnable_test, runIsNeverCalledIfGlobalRunnerIsNotCalled) {
  runnable_mock rm;
  EXPECT_CALL(rm, run()).Times(0);
}

TEST(s_runnable_test, runIsCalledOnceWhenGlobalRunnerIsCalledOnce) {
  runnable_mock rm;
  EXPECT_CALL(rm, run()).Times(1);
  global_runner();
}

TEST(s_runnable_test, runIsCalledAsManyManyTimesAsGlobalRunner) {
  runnable_mock rm;
  EXPECT_CALL(rm, run()).Times(100);
  for (int i = 0; i < 100; i++) {
    global_runner();
  }
}

TEST(s_runnable_test, multipleRunnerTest) {
  runnable_mock rm1;
  runnable_mock rm2;
  runnable_mock rm3;
  EXPECT_CALL(rm1, run).Times(100);
  EXPECT_CALL(rm2, run).Times(100);
  EXPECT_CALL(rm3, run).Times(100);
  for (int i = 0; i < 100; i++) {
    global_runner();
  }
}
#endif
