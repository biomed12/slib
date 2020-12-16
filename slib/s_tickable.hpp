#ifndef S_TICKABLE_H
#define S_TICKABLE_H

namespace simple {
struct s_tickable {
  s_tickable();
  virtual ~s_tickable();
  virtual void tick(int ms) = 0;
};
}  // namespace simple

#endif  // S_TICKABLE_HPP
