#include "Timer.h"

namespace sdds {
	Timer::Timer() {
		running = false;
	}

	void Timer::start() {
		start_time = std::chrono::steady_clock::now();
	}

	long long Timer::stop() {
		auto end_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
		return elapsed_time.count();
	}
}
