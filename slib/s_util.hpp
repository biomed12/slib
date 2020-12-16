#ifndef S_UTIL_HPP
#define S_UTIL_HPP

#include <algorithm>
#include <array>
#include <type_traits>

namespace simple {
namespace util {

inline auto insert_into = [](auto&& container, auto&& item) {
  auto it = std::find_if(container.begin(), container.end(),
                         [](auto& e) { return (e == nullptr); });

  if (it != container.end()) {
    using type = typename std::remove_reference<decltype(item)>::type;
    if constexpr (std::is_pointer_v<type>) {
      *it = item;
    } else {
      *it = &item;
    }
  }
};

inline auto remove_from = [](auto&& container, auto&& item) {
  using type = typename std::remove_reference<decltype(item)>::type;

  auto it = std::find_if(container.begin(), container.end(), [&item](auto& e) {
    if constexpr (std::is_pointer_v<type>) {
      return e == item;
    } else {
      return e == &item;
    }
  });

  if (it != container.end()) {
    *it = nullptr;
  }
};

inline auto used_of = [](auto&& container) {
  return std::count_if(container.begin(), container.end(),
                       [](auto&& e) { return (e != nullptr); });
};

inline auto size_of = [](auto&& container) { return container.size(); };

inline auto clear = [](auto&& container) {
  for (auto& e : container) {
    e = nullptr;
  }
};

inline auto invoke_for_each = [](auto&& container, auto&& f) {
  std::for_each(container.begin(), container.end(), [&f](auto& e) {
    if (e) f(e);
  });
};
}  // namespace util
}  // namespace simple

#endif  // S_UTIL_HPP
