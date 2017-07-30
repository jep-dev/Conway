#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <chrono>
#include <mutex>

namespace Mutex {
	using mutex_t = std::timed_mutex;
	using lock_t = std::unique_lock<mutex_t>;
	using std::chrono::milliseconds;

	enum Priority { normal = 0, important, critical };
	enum struct MutexStatus { ok = 0, died = 1, dying = 2 };
	enum Duration { brief = 30, extended = 50, longest = 500 };
}

#endif
