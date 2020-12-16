#ifndef S_IO_HPP
#define S_IO_HPP

#include "s_tickable.hpp"

namespace simple {

struct s_io : s_tickable {
 private:
  struct io_state {
    virtual void tick_handler(int ms, s_io* io) {
      (void)ms;
      (void)io;
    };
  };

  struct io_initial_state : io_state {
    void tick_handler(int ms, s_io* io) override {
      if (io->counter < io->threshold) {
        io->counter += ms;
      }

      if (io->counter >= io->threshold) {
        auto is_high = io->read();
        if (is_high) {
          io->raising_edge_handler();
        } else {
          io->falling_edge_handler();
        }
        io->is_high = is_high;
        io->state = &io->running_state;
        io->action_taken = true;
      }
    }
  };

  struct io_running_state : io_state {
    void tick_handler(int ms, s_io* io) override {
      // threshold'tan fazlasini sayma
      if (io->counter < io->threshold) io->counter += ms;

      // io her switch yaptiğinda counter'i resetle
      if (io->is_high != io->read()) {
        io->is_high = !io->is_high;
        io->counter = 0;
        io->action_taken = false;
      }

      // threshold kadar zaman gecmisse aksiyon al
      if (io->counter >= io->threshold) {
        if (io->action_taken == false) {
          io->take_action();
          io->action_taken = true;
        }
      }
    }
  };

 public:
  s_io(int threshold_ = 100) {
    state = &initial_state;
    threshold = threshold_;
  }
  virtual ~s_io() {}

  virtual void raising_edge_handler(void) {}
  virtual void falling_edge_handler(void) {}
  virtual bool read(void) = 0;
  virtual void tick(int ms) override { state->tick_handler(ms, this); }

 private:
  void take_action() {
    if (is_high)
      raising_edge_handler();
    else
      falling_edge_handler();
  }

 protected:
  bool is_high{false};
  int counter{0};
  int threshold{0};
  bool action_taken{false};
  io_state* state{nullptr};
  io_initial_state initial_state;
  io_running_state running_state;
};
}  // namespace simple

#endif  // S_IO_HPP
