#include "slib/s_util.hpp"

#include <array>
#include <vector>

#include "gtest/gtest.h"

#if 1
TEST(s_util_test, sizeOfAnyContainerIsCorrect) {
  struct type {};

  std::array<type*, 10> container{};
  ASSERT_EQ(container.size(), simple::util::size_of(container));
}

TEST(s_util_test, clearSlotsClearsSlots) {
  struct type {};

  std::array<type*, 10> container;
  simple::util::clear(container);

  for (auto& e : container) {
    ASSERT_EQ(e, nullptr);
  }
}

template <typename Type, auto size>
auto create_and_clear(void) {
  std::array<Type, size> container;
  simple::util::clear(container);
  return container;
}

TEST(s_util_test, insertsAtFirstEmptySlots) {
  struct type {};
  auto container = create_and_clear<type*, 10>();
  type o1;
  type o2;
  simple::util::insert_into(container, o1);
  simple::util::insert_into(container, o2);
  ASSERT_EQ(container[0], &o1);
  ASSERT_EQ(container[1], &o2);
}

TEST(s_util_test, countsFilledSlots) {
  struct type {};
  auto container = create_and_clear<type*, 10>();
  type o1;
  type o2;
  simple::util::insert_into(container, o1);
  simple::util::insert_into(container, o2);
  ASSERT_EQ(simple::util::used_of(container), 2);
}

TEST(s_util_test, popsElement) {
  struct type {};
  auto container = create_and_clear<type*, 10>();
  type o1;
  type o2;
  simple::util::insert_into(container, o1);
  simple::util::insert_into(container, o2);
  simple::util::remove_from(container, o1);
  ASSERT_EQ(simple::util::used_of(container), 1);
}

TEST(s_util_test, invokeForEachInvokesAlgorithmForAllInstance) {
  struct type {
    void foo() { is_invoked = true; }
    bool is_invoked{false};
  };

  auto container = create_and_clear<type*, 10>();
  type o1;
  type o2;
  simple::util::insert_into(container, o1);
  simple::util::insert_into(container, o2);

  simple::util::invoke_for_each(container, [](auto&& e) { e->foo(); });
  ASSERT_EQ(o1.is_invoked, true);
  ASSERT_EQ(o2.is_invoked, true);
}
#endif
