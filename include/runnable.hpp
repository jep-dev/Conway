#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

#include <chrono>
#include <cstdint>
#include <mutex>
#include <iostream>

namespace Runnable {

	using mutex_t = std::timed_mutex;
	using lock_t = std::unique_lock<mutex_t>;
	using std::chrono::milliseconds;

	enum Priority { normal = 0, important, critical };
	enum struct MutexStatus { ok = 0, died = 1, dying = 2 };
	enum Duration { brief = 30, extended = 50, longest = 500 };

	enum struct e_task : uint8_t {
		//000      001  010    011   100   101
		start=0, pause, run, error, quit, pass
	};
	std::ostream& operator<<(std::ostream &os, e_task const& e);
	template<typename D, typename... DN> struct TaskBase {
		e_task call(e_task e, DN &... dn);
		TaskBase(void);
		virtual ~TaskBase(void) = default;
	};
}

template<typename D, typename... DN>
Runnable::e_task call(Runnable::e_task e,
	Runnable::TaskBase<D,DN...> &d, DN &... dn);

#include "runnable.tpp"
#include "driver.hpp"

#endif
