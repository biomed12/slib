#include "s_tickable.hpp"

#include "s_service.hpp"
//#include "s_tick_service.hpp"

namespace simple {

// because of static initialization fiasco
using service_type = s_service<s_tickable, 50>;
service_type* tick_service{nullptr};
s_tickable::s_tickable() {
  static service_type ins;
  if (tick_service == nullptr) tick_service = &ins;
  tick_service->subscribe(this);
}
s_tickable ::~s_tickable() { tick_service->unsubscribe(this); }
}  // namespace simple

extern void global_tick(int ms) {
  simple::tick_service->serv([&ms](auto&& e) { e->tick(ms); });
}
