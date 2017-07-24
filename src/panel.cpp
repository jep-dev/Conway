#include "panel.hpp"

namespace View {
	Panel::Panel(void): TaskBase() {}
} /*
namespace Runnable {
	template<>
	e_task TaskBase<View::Panel>::call(e_task e) {
		return e_task::run;
	}
}
namespace View { */
	template<>
	e_task Panel::call(Runnable::e_task e) {
		// TODO stub
		return e;
	}

}
