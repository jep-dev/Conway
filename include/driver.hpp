#ifndef RUNNABLE_DRIVER_HPP
#define RUNNABLE_DRIVER_HPP

#include "runnable.hpp"
#include <functional>

namespace Runnable {

	template<typename... DN>
	struct Driver;

	/* TODO Figure out why each specialization (DN...) requires explicit
	   instantiation like below */

	template<>
	struct Driver<>: TaskBase<Driver<>> {
		typedef std::function<void(void)> wait_type;
		wait_type wait;
		e_task call(e_task e);
		Driver(wait_type wait);
		virtual ~Driver(void) = default;
	};
}

#endif
