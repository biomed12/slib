#ifndef S_SERVICE_H
#define S_SERVICE_H

#include "s_util.hpp"

namespace simple {
template <typename subscriber_type, auto N>
struct s_service {
  s_service() { clear(); }

  template <typename TT = subscriber_type>
  void subscribe(TT&& t) {
    util::insert_into(subscribers, std::forward<TT>(t));
  }

  template <typename TT = subscriber_type>
  void unsubscribe(TT&& t) {
    util::remove_from(subscribers, std::forward<TT>(t));
  }

  template <typename F>
  void serv(F&& f) {
    util::invoke_for_each(subscribers, std::forward<F>(f));
  }

  auto available_subscribers() { return util::used_of(subscribers); }

  void clear(void) { util::clear(subscribers); }

 private:
  std::array<subscriber_type*, N> subscribers;
};
}  // namespace simple

#endif
