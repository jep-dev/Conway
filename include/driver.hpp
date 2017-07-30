#ifndef RUNNABLE_DRIVER_HPP
#define RUNNABLE_DRIVER_HPP

#include "runnable.hpp"
#include <functional>

namespace Runnable {
	template<typename... D>
	struct Driver: TaskBase<Driver<D...>, D...> {
		typedef std::function<bool(void)> wait_type;
		wait_type wait;
		Signal call(Signal e, D &... d);
		Driver(wait_type wait);
		virtual ~Driver(void) = default;
	};
}

#endif
