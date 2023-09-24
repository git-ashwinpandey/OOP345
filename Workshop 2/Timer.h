#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds {
	class Timer {
		std::chrono::time_point<std::chrono::steady_clock> start_time;
		bool running;

	public:
		Timer();
		void start();
		long long stop();
	};
}

#endif // !SDDS_TIMER_H
