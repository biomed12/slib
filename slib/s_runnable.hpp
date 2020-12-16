#ifndef S_RUNNABLE_HPP
#define S_RUNNABLE_HPP

namespace simple {
struct s_runnable {
  s_runnable();
  virtual ~s_runnable();
  virtual void run() = 0;
};
}  // namespace simple

#endif  // S_RUNNABLE_HPP
