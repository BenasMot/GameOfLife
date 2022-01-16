#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>

class Timer {
 private:
  std::chrono::high_resolution_clock::time_point start_time;
  std::chrono::high_resolution_clock::time_point stop_time;

 public:
  void start() { start_time = std::chrono::high_resolution_clock::now(); }
  void stop() { stop_time = std::chrono::high_resolution_clock::now(); }
  int get_elapsed() { return std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time).count(); }
  static void setTimeout(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
};

#endif
