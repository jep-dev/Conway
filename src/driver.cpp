#include "driver.hpp"

namespace Runnable {
	template<typename... D>
	Driver<D...>::Driver(Driver::wait_type wait):
		wait(wait), TaskBase<Driver<D...>, D...>() {}
	template<typename... D>
	Signal Driver<D...>::call(Signal s, D &... d) {
		if(s == Restart && !wait()) return Quit;
		if(s & Signal::Start) return Start;
		if(s & Signal::Quit) return Quit;
		if(s & Signal::Fail) return Fail;
		return s;
	}

	template struct Driver<>;
}
