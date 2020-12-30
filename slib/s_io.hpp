#ifndef S_IO_HPP
#define S_IO_HPP

#include "s_runnable.hpp"
#include "s_tickable.hpp"

namespace simple {

struct s_io : s_tickable, s_runnable {
 public:
  s_io(int action_start_threshold_ = 100) : s_tickable{} {
    state = &initial_state;
    action_start_threshold = action_start_threshold_;
    is_action_taken = true;
    tick_counter = action_start_threshold_;
  }
  virtual ~s_io() {}

  virtual void raising_edge_handler(void) {}
  virtual void falling_edge_handler(void) {}
  virtual bool read(void) = 0;
  void tick(int ms) override {
    if (is_stopped) return;
    state->tick_handler(ms, this);
  }

  void run() override {
    if (is_stopped) return;
    state->run(this);
  }

  void stop(void) { is_stopped = true; }
  void start(void) { is_stopped = false; }
  void evaluate_initial_status() {
    if (read()) {
      raising_edge_handler();
    } else {
      falling_edge_handler();
    }
  }

 private:
  struct io_state {
    virtual void tick_handler(int ms, s_io *io) {
      (void)ms;
      (void)io;
    };

    virtual void run(s_io *io) { (void)io; }
  };

  struct io_initial_state : io_state {
    void tick_handler(int ms, s_io *io) override {
      if (io->tick_counter < io->action_start_threshold) {
        io->tick_counter += ms;
      }
    }

    void run(s_io *io) override {
      if (io->tick_counter >= io->action_start_threshold) {
        io->io_status = io->read();
        if (io->io_status) {
          io->raising_edge_handler();
        } else {
          io->falling_edge_handler();
        }
        io->last_handled_io_status = io->io_status;
        io->is_action_taken = true;
        io->state = &io->running_state;
      }
    }
  };

  struct io_running_state : io_state {
    void tick_handler(int ms, s_io *io) override {
      if (io->tick_counter < io->action_start_threshold) io->tick_counter += ms;
      if (io->io_status != io->read()) {
        io->tick_counter = 0;
        io->io_status = !io->io_status;
        io->is_action_taken = false;
        return;
      }
    }

    void run(s_io *io) {
      if (io->tick_counter >= io->action_start_threshold) {
        if (io->last_handled_io_status != io->io_status) {
          io->take_action();
          io->last_handled_io_status = !io->last_handled_io_status;
        }
        io->is_action_taken = true;
      }
    }
  };

  void take_action() {
    if (io_status)
      raising_edge_handler();
    else
      falling_edge_handler();
  }

 protected:
  bool io_status{false};
  bool last_handled_io_status{false};
  int tick_counter{0};
  int action_start_threshold{0};
  bool is_action_taken{false};
  bool is_stopped{false};
  io_state *state{nullptr};
  io_initial_state initial_state;
  io_running_state running_state;
};
}  // namespace simple

#endif  // S_IO_HPP
