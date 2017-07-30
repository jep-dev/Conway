#ifndef RUNNABLE_TASK_HPP
#define RUNNABLE_TASK_HPP

namespace Runnable {
	template<typename D, typename... DN> struct TaskBase {
		Signal call(Signal e, DN &... dn);
		TaskBase(void);
		virtual ~TaskBase(void) = default;
	};
}
template<typename D, typename... DN>
Runnable::Signal call(Runnable::Signal e,
	Runnable::TaskBase<D,DN...> &d, DN &... dn);

#include "task.tpp"

#endif
