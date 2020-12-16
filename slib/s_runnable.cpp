#include "s_runnable.hpp"

#include "s_service.hpp"

namespace simple {

using runnable_service_type = s_service<s_runnable, 20>;
runnable_service_type* runnables;

s_runnable::s_runnable() {
  static runnable_service_type ins;
  if (runnables == nullptr) {
    runnables = &ins;
  }
  runnables->subscribe(this);
}
s_runnable::~s_runnable() { runnables->unsubscribe(this); }

}  // namespace simple

extern void global_runner(void) {
  simple::runnables->serv([](auto& e) { e->run(); });
}
