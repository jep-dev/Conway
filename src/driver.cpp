#include "driver.hpp"

namespace Runnable {
	Driver<>::Driver(Driver::wait_type wait):
		wait(wait), TaskBase() {}
	e_task Driver<>::call(e_task e) {
		switch(e) {
			case e_task::pause:
			case e_task::run:   return e;
			case e_task::pass:  return e_task::start;
			case e_task::start: return wait() ? e_task::run : e_task::quit;
			default:            return e_task::quit;
		}
			// case e_task::start: wait(); return e_task::run;
	}
}
