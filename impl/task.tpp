#ifndef RUNNABLE_TASK_TPP
#define RUNNABLE_TASK_TPP

namespace Runnable {
	template<typename D, typename... DN>
	TaskBase<D,DN...>::TaskBase(void) {}
	template<typename D, typename... DN>
	Signal TaskBase<D,DN...>::call(Signal s, DN &... dn) {
		return static_cast<D*>(this) -> call(s, dn...);
	}
}
template<typename D, typename... DN>
Runnable::Signal call(Runnable::Signal sig,
	Runnable::TaskBase<D,DN...> &d, DN &... dn)
{
	return d.call(sig, dn...);
}

#endif
