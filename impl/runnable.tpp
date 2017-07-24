#ifndef RUNNABLE_TPP
#define RUNNABLE_TPP

namespace Runnable {
	template<typename D, typename... DN>
	e_task TaskBase<D,DN...>::call(e_task e, DN &... dn) {
		return static_cast<D*>(this) -> call(e, dn...);
	}
}
template<typename D, typename... DN>
Runnable::e_task call(Runnable::e_task e,
	Runnable::TaskBase<D,DN...> &d, DN &... dn) {
	return d.call(e, dn...);
}

#endif
